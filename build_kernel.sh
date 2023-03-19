export ARCH=arm64
export SUBARCH=arm64
export ak=$HOME/AnyKernel3
export PATH="$HOME/llvm-16.0.0/bin:$PATH"

MAKE_PARAMS="LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-none-eabi-"
git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make $MAKE_PARAMS renoir_defconfig -j9
make $MAKE_PARAMS Image dtbs dtbo.img -j9

if [ $? -ne 0 ]
then
    exit 1
fi

NAME=$(git describe --exact-match --tags 2> /dev/null || git rev-parse --short HEAD)
cp out/arch/arm64/boot/Image $ak/Image
find out/arch/arm64/boot/dts -name '*.dtb' -exec cat {} + > $ak/dtb
cp out/arch/arm64/boot/dtbo.img $ak/dtbo.img
cd $ak
zip -FSr9 $NAME.zip ./*  -x "*.zip"
echo "Kernel zip name: $NAME"
