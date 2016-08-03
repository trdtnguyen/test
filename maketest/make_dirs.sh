#dirs names
OBJ=obj
BIN=bin
LIB=lib
SRC=src
INC=inc

BUILD_DIRS="$OBJ $BIN $LIB $SRC $INC"

for D in $BUILD_DIRS
do
	if [ ! -d ${D} ]
	then
		mkdir ${D}
	fi
done
