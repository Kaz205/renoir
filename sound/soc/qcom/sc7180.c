// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 *
 * sc7180.c -- ALSA SoC Machine driver for SC7180
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/jack.h>
#include <sound/soc.h>
#include <uapi/linux/input-event-codes.h>
#include <dt-bindings/sound/sc7180-lpass.h>
#include "../codecs/rt5682.h"
#include "common.h"
#include "lpass.h"

#define DEFAULT_SAMPLE_RATE_48K		48000
#define DEFAULT_MCLK_RATE		19200000
#define RT5682_PLL1_FREQ (48000 * 512)

static int sc7180_parse_of(struct snd_soc_card *card)
{
	struct device_node *np;
	struct device_node *codec = NULL;
	struct device_node *platform = NULL;
	struct device_node *cpu = NULL;
	struct device *dev = card->dev;
	struct snd_soc_dai_link *link;
	struct of_phandle_args args;
	struct snd_soc_dai_link_component *dlc;
	int ret, num_links, dir;

	ret = snd_soc_of_parse_card_name(card, "model");
	if (ret) {
		dev_err(dev, "Error parsing card name: %d\n", ret);
		return ret;
	}

	/* DAPM routes */
	if (of_property_read_bool(dev->of_node, "audio-routing")) {
		ret = snd_soc_of_parse_audio_routing(card,
						     "audio-routing");
		if (ret)
			return ret;
	}

	/* Populate links */
	num_links = of_get_child_count(dev->of_node);

	/* Allocate the DAI link array */
	card->dai_link = kcalloc(num_links, sizeof(*link), GFP_KERNEL);
	if (!card->dai_link)
		return -ENOMEM;

	card->num_links = num_links;
	link = card->dai_link;

	for_each_child_of_node(dev->of_node, np) {
		dlc = devm_kzalloc(dev, 2 * sizeof(*dlc), GFP_KERNEL);
		if (!dlc)
			return -ENOMEM;

		link->cpus	= &dlc[0];
		link->platforms	= &dlc[1];

		link->num_cpus		= 1;
		link->num_platforms	= 1;

		ret = of_property_read_string(np, "link-name", &link->name);
		if (ret) {
			dev_err(card->dev, "error getting codec dai_link name\n");
			goto err;
		}

		of_property_read_u32(np, "unidirectional", &dir);
		if (dir == 0)
			link->playback_only = 1;
		else if (dir == 1)
			link->capture_only = 1;

		cpu = of_get_child_by_name(np, "cpu");
		codec = of_get_child_by_name(np, "codec");

		if (!cpu) {
			dev_err(dev, "%s: Can't find cpu DT node\n",
				link->name);
			ret = -EINVAL;
			goto err;
		}

		ret = of_parse_phandle_with_args(cpu, "sound-dai",
						 "#sound-dai-cells", 0, &args);
		if (ret) {
			dev_err(card->dev, "%s: error getting cpu phandle\n",
				link->name);
			goto err;
		}
		link->cpus->of_node = args.np;
		link->id = args.args[0];

		ret = snd_soc_of_get_dai_name(cpu, &link->cpus->dai_name);
		if (ret) {
			dev_err(card->dev, "%s: error getting cpu dai name\n",
				link->name);
			goto err;
		}

		if (codec) {
			ret = snd_soc_of_get_dai_link_codecs(dev, codec, link);
			if (ret < 0) {
				dev_err(card->dev, "%s: codec dai not found\n",
					link->name);
				goto err;
			}
		} else {
			dlc = devm_kzalloc(dev, sizeof(*dlc), GFP_KERNEL);
			if (!dlc)
				return -ENOMEM;

			link->codecs	 = dlc;
			link->num_codecs = 1;

			link->codecs->dai_name = "snd-soc-dummy-dai";
			link->codecs->name = "snd-soc-dummy";
		}

		link->platforms->of_node = link->cpus->of_node;
		link->stream_name = link->name;
		link++;

		of_node_put(cpu);
		of_node_put(codec);
	}

	return 0;
err:
	of_node_put(np);
	of_node_put(cpu);
	of_node_put(codec);
	of_node_put(platform);
	kfree(card->dai_link);
	return ret;
}

struct sc7180_snd_data {
	struct snd_soc_jack jack;
	bool jack_setup;
	struct snd_soc_card *card;
	u32 pri_mi2s_clk_count;
};

static int sc7180_snd_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	int ret = 0;

	switch (cpu_dai->id) {
	case MI2S_PRIMARY:
		break;
	case MI2S_SECONDARY:
		break;
	default:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		break;
	}
	return ret;
}

static void sc7180_jack_free(struct snd_jack *jack)
{
	struct snd_soc_component *component = jack->private_data;

	snd_soc_component_set_jack(component, NULL, NULL);
}

static int sc7180_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	struct snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	struct sc7180_snd_data *pdata = snd_soc_card_get_drvdata(card);
	struct snd_jack *jack;
	int rval;

	if (!pdata->jack_setup) {
		rval = snd_soc_card_jack_new(
				card, "Headset Jack",
				SND_JACK_HEADSET |
				SND_JACK_HEADPHONE |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&pdata->jack, NULL, 0);

		if (rval < 0) {
			dev_err(card->dev, "Unable to add Headphone Jack\n");
			return rval;
		}

		jack = pdata->jack.jack;

		snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
		snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
		snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
		snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);
		pdata->jack_setup = true;
	}

	switch (cpu_dai->id) {
	case MI2S_PRIMARY:
		jack  = pdata->jack.jack;
		component = codec_dai->component;

		jack->private_data = component;
		jack->private_free = sc7180_jack_free;
		rval = snd_soc_component_set_jack(component,
						  &pdata->jack, NULL);
		if (rval != 0 && rval != -EOPNOTSUPP) {
			dev_warn(card->dev, "Failed to set jack: %d\n", rval);
			return rval;
		}
		break;
	case MI2S_SECONDARY:
		break;
	default:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		break;
	}

	return 0;
}

static int sc7180_snd_startup(struct snd_pcm_substream *substream)
{
	unsigned int codec_dai_fmt = SND_SOC_DAIFMT_CBS_CFS;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct sc7180_snd_data *data = snd_soc_card_get_drvdata(card);
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	struct snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	int ret;

	switch (cpu_dai->id) {
	case MI2S_PRIMARY:
		codec_dai_fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_I2S;
		if (++data->pri_mi2s_clk_count == 1) {
			snd_soc_dai_set_sysclk(cpu_dai,
					       LPASS_MCLK0,
					       DEFAULT_MCLK_RATE,
					       SNDRV_PCM_STREAM_PLAYBACK);
		}
		snd_soc_dai_set_fmt(codec_dai, codec_dai_fmt);

		/* Configure PLL1 for codec */
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT5682_PLL1_S_MCLK,
					  DEFAULT_MCLK_RATE, RT5682_PLL1_FREQ);
		if (ret < 0) {
			dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
			return ret;
		}

		/* Configure sysclk for codec */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL1,
					     RT5682_PLL1_FREQ,
					     SND_SOC_CLOCK_IN);
		if (ret < 0)
			dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n",
				ret);

		break;
	case MI2S_SECONDARY:
		break;
	default:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		break;
	}
	return 0;
}

static void  sc7180_snd_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct sc7180_snd_data *data = snd_soc_card_get_drvdata(card);
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	switch (cpu_dai->id) {
	case MI2S_PRIMARY:
		if (--data->pri_mi2s_clk_count == 0) {
			snd_soc_dai_set_sysclk(cpu_dai,
					       LPASS_MCLK0,
					       0,
					       SNDRV_PCM_STREAM_PLAYBACK);
		}
		break;
	case MI2S_SECONDARY:
		break;
	default:
		pr_err("%s: invalid dai id 0x%x\n", __func__, cpu_dai->id);
		break;
	}
}

static const struct snd_soc_ops sc7180_be_ops = {
	.hw_params = sc7180_snd_hw_params,
	.startup = sc7180_snd_startup,
	.shutdown = sc7180_snd_shutdown,
};

static const struct snd_soc_dapm_widget sc7180_snd_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NULL),
	SND_SOC_DAPM_MIC("Headset Mic", NULL),
};

static void sc7180_add_ops(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *link;
	int i;

	for_each_card_prelinks(card, i, link) {
		link->ops = &sc7180_be_ops;
		link->init = sc7180_dai_init;
	}
}

static int sc7180_snd_platform_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card;
	struct sc7180_snd_data *data;
	struct device *dev = &pdev->dev;
	int ret;

	card = kzalloc(sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	/* Allocate the private data */
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto data_alloc_fail;
	}

	card->dapm_widgets = sc7180_snd_widgets;
	card->num_dapm_widgets = ARRAY_SIZE(sc7180_snd_widgets);
	card->dev = dev;
	dev_set_drvdata(dev, card);
	ret = sc7180_parse_of(card);
	if (ret) {
		dev_err(dev, "Error parsing OF data\n");
		goto parse_dt_fail;
	}

	data->card = card;
	snd_soc_card_set_drvdata(card, data);

	sc7180_add_ops(card);
	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(dev, "Sound card registration failed\n");
		goto register_card_fail;
	}
	return ret;

register_card_fail:
	kfree(card->dai_link);
parse_dt_fail:
	kfree(data);
data_alloc_fail:
	kfree(card);
	return ret;
}

static int sc7180_snd_platform_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = dev_get_drvdata(&pdev->dev);
	struct sc7180_snd_data *data = snd_soc_card_get_drvdata(card);

	snd_soc_unregister_card(card);
	kfree(card->dai_link);
	kfree(data);
	kfree(card);
	return 0;
}

static const struct of_device_id sc7180_snd_device_id[]  = {
	{ .compatible = "qcom,sc7180-sndcard" },
	{},
};
MODULE_DEVICE_TABLE(of, sc7180_snd_device_id);

static struct platform_driver sc7180_snd_driver = {
	.probe = sc7180_snd_platform_probe,
	.remove = sc7180_snd_platform_remove,
	.driver = {
		.name = "msm-snd-sc7180",
		.of_match_table = sc7180_snd_device_id,
	},
};
module_platform_driver(sc7180_snd_driver);

MODULE_DESCRIPTION("sc7180 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
