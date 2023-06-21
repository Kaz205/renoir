export ARCH=arm64
export SUBARCH=arm64
export ak=$HOME/AnyKernel3
export PATH="$HOME/llvm-16.0.6/bin:$PATH"

NAME=$(git describe --exact-match --tags 2> /dev/null || git rev-parse --short HEAD)
MAKE_PARAMS="LLVM=1 LLVM_IAS=1"
git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make $MAKE_PARAMS renoir_defconfig -j$(nproc --all)
make $MAKE_PARAMS Image dtbs dtbo.img -j$(nproc --all)

if [ $? -ne 0 ]
then
    exit 1
fi

cp out/arch/arm64/boot/Image $ak/Image
find out/arch/arm64/boot/dts -name '*.dtb' -exec cat {} + > $ak/dtb
cp out/arch/arm64/boot/dtbo.img $ak/dtbo.img
cd $ak
zip -FSr9 $NAME.zip ./*  -x "*.zip"
echo "Kernel zip name: $NAME"
