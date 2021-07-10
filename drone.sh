export ARCH=arm64
export SUBARCH=arm64
export ak=AnyKernel3
export CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=/usr/bin/arm-none-eabi-

git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make clean -j$(nproc --all) && make mrproper -j$(nproc --all)
make renoir_defconfig -j$(nproc --all)
make -j$(nproc --all) Image.gz

if [ $? -ne 0 ]
then
    exit 1
fi

cp out/arch/arm64/boot/Image.gz $ak/Image.gz
cd $ak
zip -FSr9 kernel.zip ./*
