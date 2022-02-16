export ARCH=arm64
export SUBARCH=arm64
export ak=AnyKernel3
export PATH="/drone/src/google-clang/clang-r445002/bin:$PATH"

MAKE_PARAMS="CC=clang CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 \
	CROSS_COMPILE=/drone/src/arm64-gcc/bin/aarch64-elf- \
	CROSS_COMPILE_COMPAT=/drone/src/arm32-gcc/bin/arm-eabi- \
    LD=ld.lld \
	AR=llvm-ar \
	NM=llvm-nm \
	OBJCOPY=llvm-objcopy \
	OBJDUMP=llvm-objdump \
	STRIP=llvm-strip"
git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make clean -j$(nproc --all) && make mrproper -j$(nproc --all)
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
zip -FSr9 kernel.zip ./*
