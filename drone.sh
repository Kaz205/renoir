export ARCH=arm64
export SUBARCH=arm64
export home=/drone/src
export ak=$home/AnyKernel3
export PATH="$home/google-clang/bin:$PATH"

MAKE_PARAMS="CC=clang CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 \
	CROSS_COMPILE=$home/arm64-gcc/bin/aarch64-elf- \
	CROSS_COMPILE_COMPAT=$home/arm32-gcc/bin/arm-eabi- \
	LD=ld.lld \
	AR=llvm-ar \
	NM=llvm-nm \
	OBJCOPY=llvm-objcopy \
	OBJDUMP=llvm-objdump \
	STRIP=llvm-strip"
git submodule init && git submodule update

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
make $MAKE_PARAMS renoir_defconfig -j$(nproc --all)
make $MAKE_PARAMS Image dtbs dtbo.img -j$(nproc --all)

if [ $? -ne 0 ]
then
    exit 1
fi

NAME=$(git describe --exact-match --tags 2> /dev/null || git rev-parse --short HEAD)
cp out/arch/arm64/boot/Image $ak/Image
find out/arch/arm64/boot/dts -name '*.dtb' -exec cat {} + > $ak/dtb
cp out/arch/arm64/boot/dtbo.img $ak/dtbo.img
cd $ak
zip -FSr9 $NAME.zip ./*
