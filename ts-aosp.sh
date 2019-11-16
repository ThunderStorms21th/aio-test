#!/bin/bash
#
# Thanks to Tkkg1994 and djb77 for the script
#
# Thanks to MoRoGoku for the script
# Kernel Build Script v1.9, modified by ThunderStorms Team
#

# SETUP
# -----
export ARCH=arm64
export SUBARCH=arm64
CCACHE="$(command -v ccache)"
export CCACHE

export BUILD_CROSS_COMPILE=~/kernel/toolchain/aarch64-linux-android-4.9/bin/aarch64-linux-android-

export CROSS_COMPILE="${CCACHE} $BUILD_CROSS_COMPILE"
BUILD_JOB_NUMBER="$(grep -c '^processor' /proc/cpuinfo)"
export BUILD_JOB_NUMBER

export ANDROID_MAJOR_VERSION=o
export PLATFORM_VERSION=8.0.0
export ANDROID_VERSION=80000
export CURRENT_ANDROID_MAJOR_VERSION=o
KBUILD_CFLAGS += -DANDROID_VERSION=80000
KBUILD_CFLAGS += -DANDROID_MAJOR_VERSION=o
export BUILD_PLATFORM_VERSION=8.0.0

RDIR=$(pwd)
OUTDIR=$RDIR/arch/$ARCH/boot
DTSDIR=$RDIR/arch/$ARCH/boot/dts
DTBDIR=$OUTDIR/dtb
DTCTOOL=$RDIR/scripts/dtc/dtc
INCDIR=$RDIR/include
PAGE_SIZE=2048
DTB_PADDING=0

DEFCONFIG=ts-a-kernel_defconfig
DEFCONFIG_S7EDGE=hero2lte_defconfig
DEFCONFIG_S7FLAT=herolte_defconfig

export K_VERSION="v1.2"
export K_BASE="S5CSF1"
export K_NAME="ThundeRStormS-Kernel"
export REVISION="RC"
export KBUILD_BUILD_VERSION="1"
S7DEVICE="OREO"
EDGE_LOG=Edge_build.log
FLAT_LOG=Flat_build.log
PORT=0


# FUNCTIONS
# ---------
FUNC_DELETE_PLACEHOLDERS()
{
	find . -name \.placeholder -type f -delete
        echo "Placeholders Deleted from Ramdisk"
        echo ""
}

FUNC_CLEAN_DTB()
{
	if ! [ -d "$RDIR"/arch/$ARCH/boot/dts ] ; then
		echo "no directory : ""$RDIR"/arch/$ARCH/boot/dts""
	else
		echo "rm files in : ""$RDIR"/arch/$ARCH/boot/dts/*.dtb""
		rm "$RDIR"/arch/$ARCH/boot/dts/*.dtb
		rm "$RDIR"/arch/$ARCH/boot/dtb/*.dtb
		rm "$RDIR"/arch/$ARCH/boot/boot.img-dtb
		rm "$RDIR"/arch/$ARCH/boot/boot.img-zImage
	fi
}

FUNC_BUILD_KERNEL()
{
	echo ""
        echo "build common config=""$KERNEL_DEFCONFIG" ""
        echo "build variant config=""$MODEL" ""

	cp -f "$RDIR"/arch/$ARCH/configs/$DEFCONFIG "$RDIR"/arch/$ARCH/configs/tmp_defconfig
	cat "$RDIR"/arch/$ARCH/configs/"$KERNEL_DEFCONFIG" >> "$RDIR"/arch/$ARCH/configs/tmp_defconfig

	#FUNC_CLEAN_DTB

	make -j"$BUILD_JOB_NUMBER" ARCH=$ARCH \
			 \
			tmp_defconfig || exit -1
	make -j"$BUILD_JOB_NUMBER" ARCH=$ARCH \
			 || exit -1
	echo ""

	rm -f "$RDIR"/arch/$ARCH/configs/tmp_defconfig
}

FUNC_BUILD_DTB()
{
	[ -f "$DTCTOOL" ] || {
		echo "You need to run ./ts_builder.sh first!"
		exit 1
	}
	case $MODEL in
	G930)
		DTSFILES="exynos8890-herolte_eur_open_aosp_04 exynos8890-herolte_eur_open_aosp_08
				exynos8890-herolte_eur_open_aosp_09 exynos8890-herolte_eur_open_aosp_10"
		;;
	G935)
		DTSFILES="exynos8890-hero2lte_eur_open_aosp_04 exynos8890-hero2lte_eur_open_aosp_08"
		;;
	*)

		echo "Unknown device: $MODEL"
		exit 1
		;;
	esac
	mkdir -p "$OUTDIR" "$DTBDIR"
	cd "$DTBDIR" || {
		echo "Unable to cd to $DTBDIR!"
		exit 1
	}
	rm -f ./*
	echo "Processing dts files."
	for dts in $DTSFILES; do
		echo "=> Processing: ${dts}.dts"
		"${BUILD_CROSS_COMPILE}"cpp -nostdinc -undef -x assembler-with-cpp -I "$INCDIR" "$DTSDIR/${dts}.dts" > "${dts}.dts"
		echo "=> Generating: ${dts}.dtb"
		$DTCTOOL -p $DTB_PADDING -i "$DTSDIR" -O dtb -o "${dts}.dtb" "${dts}.dts"
	done
	echo "Generating dtb.img."
	"$RDIR"/scripts/dtbtool_exynos/dtbtool -o "$OUTDIR/dtb.img" -d "$DTBDIR/" -s $PAGE_SIZE
	echo "Done."
}

FUNC_BUILD_RAMDISK()
{
	echo ""
	echo "Building Ramdisk"
	mv "$RDIR"/arch/$ARCH/boot/Image "$RDIR"/arch/$ARCH/boot/boot.img-zImage
	mv "$RDIR"/arch/$ARCH/boot/dtb.img "$RDIR"/arch/$ARCH/boot/boot.img-dtb
	
	cd "$RDIR"/builds || exit
	mkdir temp
	cp -rf aik/. temp
	cp -rf LOS16/. temp
	
	rm -f temp/split_img/boot.img-zImage
	rm -f temp/split_img/boot.img-dtb
	mv "$RDIR"/arch/$ARCH/boot/boot.img-zImage temp/split_img/boot.img-zImage
	mv "$RDIR"/arch/$ARCH/boot/boot.img-dtb temp/split_img/boot.img-dtb
	cd temp || exit

	case $MODEL in
	G935)
		echo "Ramdisk for G935"
		;;
	G930)
		echo "Ramdisk for G930"

		sed -i 's/SRPOI30A003KU/SRPOI17A003KU/g' split_img/boot.img-board

		sed -i 's/G935/G930/g' ramdisk/default.prop
		sed -i 's/hero2/hero/g' ramdisk/default.prop
		;;
	esac

		echo "Done"

	./repackimg.sh

	cp -f image-new.img "$RDIR"/builds
	cd ..
	rm -rf temp
	echo SEANDROIDENFORCE >> image-new.img
	mv image-new.img "$MODEL"-boot.img
}

FUNC_BUILD_FLASHABLES()
{
	cd "$RDIR"/builds || exit
	mkdir temp2
	cp -rf zip-a/common/. temp2
    	mv *.img temp2/
	cd temp2 || exit
	echo ""
	echo "Compressing kernels..."
	tar cv *.img | xz -9 > kernel.tar.xz
	mv kernel.tar.xz ts/
	rm -f *.img

	zip -9 -r ../"$ZIP_NAME" *

	cd ..
    	rm -rf temp2

}



# MAIN PROGRAM
# ------------

MAIN()
{

(
        START=$(date +"%s")
	FUNC_DELETE_PLACEHOLDERS
	FUNC_BUILD_KERNEL
	FUNC_BUILD_DTB
	FUNC_BUILD_RAMDISK
	FUNC_BUILD_FLASHABLES
        END=$(date +"%s")
        DIFF=$((END - START))
        echo -e "Build took $((DIFF / 60)) minute(s) and $((DIFF % 60)) seconds."
	echo ""
) 2>&1 | tee -a ./"$LOG"

	echo "Your flasheable release can be found in the build folder"
	echo ""
}

MAIN2()
{

(
        START=$(date +"%s")
	FUNC_DELETE_PLACEHOLDERS
	FUNC_BUILD_KERNEL
	FUNC_BUILD_DTB
	FUNC_BUILD_RAMDISK
        END=$(date +"%s")
        DIFF=$((END - START))
        echo -e "Build took $((DIFF / 60)) minute(s) and $((DIFF % 60)) seconds."
	echo ""
) 2>&1 | tee -a ./"$LOG"

	echo "Your flasheable release can be found in the build folder"
	echo ""
}


# PROGRAM START
# -------------
clear
echo "*****************************************"
echo "*   ThunderStorms Kernel Build Script   *"
echo "*****************************************"
echo ""
echo "    CUSTOMIZABLE STOCK SAMSUNG KERNEL"
echo ""
echo "           Build Kernel for:"
echo ""
echo "S7 LOS16"
echo "(1) S7 Flat SM-G930F/FD"
echo "(2) S7 Edge SM-G935F/FD"
echo "(3) S7 Edge + Flat F/FD"
echo ""
echo ""
read -p "Select an option to compile the kernel " prompt


if [ "$prompt" == "1" ]; then
    MODEL=G930
    DEVICE=$S7DEVICE
    KERNEL_DEFCONFIG=$DEFCONFIG_S7FLAT
    LOG=$FLAT_LOG
    ZIP_DATE=$(date +%Y%m%d)
    export KERNEL_VERSION="$K_NAME-$K_BASE-LOS16-$K_VERSION"
    echo "S7 Flat G930F Selected"
    ZIP_NAME=$K_NAME-$MODEL-LOS16-$K_VERSION-$ZIP_DATE.zip
    MAIN
elif [ "$prompt" == "2" ]; then
    MODEL=G935
    DEVICE=$S7DEVICE
    KERNEL_DEFCONFIG=$DEFCONFIG_S7EDGE
    LOG=$EDGE_LOG
    ZIP_DATE=$(date +%Y%m%d)
    export KERNEL_VERSION="$K_NAME-$K_BASE-LOS16-$K_VERSION"
    echo "S7 Edge G935F Selected"
    ZIP_NAME=$K_NAME-$MODEL-LOS16-$K_VERSION-$ZIP_DATE.zip
    MAIN
elif [ "$prompt" == "3" ]; then
    MODEL=G935
    DEVICE=$S7DEVICE
    KERNEL_DEFCONFIG=$DEFCONFIG_S7EDGE
    LOG=$EDGE_LOG
    ZIP_DATE=$(date +%Y%m%d)
    export KERNEL_VERSION="$K_NAME-$K_BASE-LOS16-$K_VERSION"
    echo "S7 EDGE + FLAT Selected"
    echo "Compiling EDGE ..."
    MAIN2
    MODEL=G930
    KERNEL_DEFCONFIG=$DEFCONFIG_S7FLAT
    LOG=$FLAT_LOG
    export KERNEL_VERSION="$K_NAME-$K_BASE-LOS16-$K_VERSION"
    echo "Compiling FLAT ..."
    ZIP_NAME=$K_NAME-G93X-LOS16-$K_VERSION-$ZIP_DATE.zip
    MAIN
fi


