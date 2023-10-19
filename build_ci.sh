export ARCH=arm64
export SUBARCH=arm64
export ak="$(pwd)/AnyKernel3"
export PATH="$(pwd)/llvm-17.0.3/bin:$PATH"

NAME=$(git describe --exact-match --tags 2> /dev/null || git rev-parse --short HEAD)
MAKE_PARAMS="LLVM=1 LLVM_IAS=1"

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
git submodule init && git submodule update --depth=1

# Enable thinlto
sed -i "/THINLTO/d" arch/arm64/configs/renoir_defconfig
make $MAKE_PARAMS renoir_defconfig -j$(nproc --all)
make $MAKE_PARAMS Image dtbs dtbo.img -j$(nproc --all)

if [ $? -ne 0 ]
then
    exit 1
fi

# actions/upload-artifact automatically zips the artifacts, so no need to manually zip
echo "name=$NAME" >> $GITHUB_ENV
cp out/arch/arm64/boot/Image $ak/Image
find out/arch/arm64/boot/dts -name '*.dtb' -exec cat {} + > $ak/dtb
cp out/arch/arm64/boot/dtbo.img $ak/dtbo.img
