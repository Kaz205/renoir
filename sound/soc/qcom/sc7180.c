// SPDX-License-Identifier: GPL-2.0-only
//
// Copyright (c) 2020, The Linux Foundation. All rights reserved.
//
// sc7180.c -- ALSA SoC Machine driver for SC7180

#include <dt-bindings/sound/sc7180-lpass.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <sound/core.h>
#include <sound/jack.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <uapi/linux/input-event-codes.h>

#include "../codecs/rt5682.h"
#include "common.h"
#include "lpass.h"

#define DEFAULT_SAMPLE_RATE_48K		48000
#define DEFAULT_MCLK_RATE		19200000
#define RT5682_PLL1_FREQ (48000 * 512)

struct sc7180_snd_data {
	struct snd_soc_jack jack;
	u32 pri_mi2s_clk_count;
};

static void sc7180_jack_free(struct snd_jack *jack)
{
	struct snd_soc_component *component = jack->private_data;

	snd_soc_component_set_jack(component, NULL, NULL);
}

static int sc7180_headset_init(struct snd_soc_component *component)
{
	struct snd_soc_card *card = component->card;
	struct sc7180_snd_data *pdata = snd_soc_card_get_drvdata(card);
	struct snd_jack *jack;
	int rval;

	rval = snd_soc_card_jack_new(
			card, "Headset Jack",
			SND_JACK_HEADSET |
			SND_JACK_HEADPHONE |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3,
			&pdata->jack, NULL, 0);

	if (rval < 0) {
		dev_err(card->dev, "Unable to add Headset Jack\n");
		return rval;
	}

	jack = pdata->jack.jack;

	snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	jack->private_data = component;
	jack->private_free = sc7180_jack_free;

	rval = snd_soc_component_set_jack(component,
					  &pdata->jack, NULL);
	if (rval != 0 && rval != -EOPNOTSUPP) {
		dev_warn(card->dev, "Failed to set jack: %d\n", rval);
		return rval;
	}

	return 0;
}

static struct snd_soc_aux_dev sc7180_headset_dev = {
	.dlc = COMP_EMPTY(),
	.init = sc7180_headset_init,
};

static int sc7180_snd_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct sc7180_snd_data *data = snd_soc_card_get_drvdata(card);
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	struct snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	int ret;

	switch (cpu_dai->id) {
	case MI2S_PRIMARY:
		if (++data->pri_mi2s_clk_count == 1) {
			snd_soc_dai_set_sysclk(cpu_dai,
					       LPASS_MCLK0,
					       DEFAULT_MCLK_RATE,
					       SNDRV_PCM_STREAM_PLAYBACK);
		}

		snd_soc_dai_set_fmt(codec_dai,
				    SND_SOC_DAIFMT_CBS_CFS |
				    SND_SOC_DAIFMT_NB_NF |
				    SND_SOC_DAIFMT_I2S);

		/* Configure PLL1 for codec */
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT5682_PLL1_S_MCLK,
					  DEFAULT_MCLK_RATE, RT5682_PLL1_FREQ);
		if (ret) {
			dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
			return ret;
		}

		/* Configure sysclk for codec */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL1,
					     RT5682_PLL1_FREQ,
					     SND_SOC_CLOCK_IN);
		if (ret)
			dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n",
				ret);

		break;
	case MI2S_SECONDARY:
		break;
	default:
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		return -EINVAL;
	}
	return 0;
}

static void sc7180_snd_shutdown(struct snd_pcm_substream *substream)
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
		dev_err(rtd->dev, "%s: invalid dai id 0x%x\n", __func__,
			cpu_dai->id);
		break;
	}
}

static const struct snd_soc_ops sc7180_ops = {
	.startup = sc7180_snd_startup,
	.shutdown = sc7180_snd_shutdown,
};

static const struct snd_soc_dapm_widget sc7180_snd_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NULL),
	SND_SOC_DAPM_MIC("Headset Mic", NULL),
};

static struct snd_soc_card sc7180_card = {
	.owner = THIS_MODULE,
	.aux_dev = &sc7180_headset_dev,
	.num_aux_devs = 1,
	.dapm_widgets = sc7180_snd_widgets,
	.num_dapm_widgets = ARRAY_SIZE(sc7180_snd_widgets),
};

static int sc7180_parse_aux_of(struct device *dev)
{
	sc7180_headset_dev.dlc.of_node = of_parse_phandle(
			dev->of_node, "aux-dev", 0);

	if (!sc7180_headset_dev.dlc.of_node)
		return -EINVAL;
	return 0;
}

static void sc7180_add_ops(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *link;
	int i;

	for_each_card_prelinks(card, i, link)
		link->ops = &sc7180_ops;
}

static int sc7180_snd_platform_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &sc7180_card;
	struct sc7180_snd_data *data;
	struct device *dev = &pdev->dev;
	int ret;

	/* Allocate the private data */
	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	card->dev = dev;

	ret = qcom_snd_parse_of(card);
	if (ret) {
		dev_err(dev, "Error parsing OF data\n");
		return ret;
	}

	snd_soc_card_set_drvdata(card, data);

	sc7180_add_ops(card);

	ret = sc7180_parse_aux_of(dev);
	if (ret) {
		dev_err(dev, "Failed to parse OF for jack device\n");
		return ret;
	}

	return devm_snd_soc_register_card(dev, card);
}

static const struct of_device_id sc7180_snd_device_id[]  = {
	{ .compatible = "qcom,sc7180-sndcard" },
	{},
};
MODULE_DEVICE_TABLE(of, sc7180_snd_device_id);

static struct platform_driver sc7180_snd_driver = {
	.probe = sc7180_snd_platform_probe,
	.driver = {
		.name = "msm-snd-sc7180",
		.of_match_table = sc7180_snd_device_id,
	},
};
module_platform_driver(sc7180_snd_driver);

MODULE_DESCRIPTION("sc7180 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
