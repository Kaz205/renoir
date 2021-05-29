export ARCH=arm64
export SUBARCH=arm64
export ak=AnyKernel3
export CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=/usr/bin/arm-none-eabi-

git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make clean -j$(nproc --all) && make mrproper -j$(nproc --all)
make floral_defconfig -j$(nproc --all)
make -j$(nproc --all) Image.lz4 dtbs dtbo.img

if [ $? -ne 0 ]
then
    exit 1
fi

cp out/arch/arm64/boot/Image.lz4 $ak/Image.lz4
find out/arch/arm64/boot/dts -name '*.dtb' -exec cat {} + > $ak/dtb
cp out/arch/arm64/boot/dtb $ak/dtb
cp out/arch/arm64/boot/dtbo.img $ak/dtbo.img
cd $ak
zip -FSr9 kernel.zip ./*
