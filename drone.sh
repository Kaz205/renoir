export ARCH=arm64
export SUBARCH=arm64
export ak=AnyKernel3
export CLANG_DIR=google-clang/clang-r433403/bin
export LLVM=1
export CLANG_TRIPLE=aarch64-linux-gnu
export CROSS_COMPILE=$CLANG_DIR/aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=$CLANG_DIR/arm-linux-gnueabi-

git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make clean -j$(nproc --all) && make mrproper -j$(nproc --all)
make renoir_defconfig -j$(nproc --all)
make -j$(nproc --all) Image dtbs dtbo.img

if [ $? -ne 0 ]
then
    exit 1
fi

cp out/arch/arm64/boot/Image $ak/Image
find out/arch/arm64/boot/dts -name '*.dtb' -exec cat {} + > $ak/dtb
cp out/arch/arm64/boot/dtbo.img $ak/dtbo.img
cd $ak
zip -FSr9 kernel.zip ./*
