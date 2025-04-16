#toolchain
TOOLCHAIN=aarch64-linux-gnu-
CC=${TOOLCHAIN}gcc
STRIP=${TOOLCHAIN}strip
LIBS="-linova_ai_cam -ljpeg"

#dirs
DIR=$(cd `dirname $0`;pwd)
LIBDIR=$DIR/libs/
mkdir -p $LIB

#build libs
LIBSRC1=$DIR/camera/
make -C $LIBSRC1 clean
make -C $LIBSRC1
make -C $LIBSRC1 install
#LIBSRC2 = $DIR/network/
#make -C $LIBSRC2 clean
#make -C $LIBSRC2
#make -C $LIBSRC2 install

$CC -I$LIBDIR -o test test.c -L$LIBDIR $LIBS
