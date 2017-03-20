#!/bin/sh

if [ $# -ne 2 ]; then
	echo "Usage: ./loopback.sh [infile.wav] [outfile.wav]"
	exit
fi;
NAME_IN=`basename $1 .wav`
NAME_OUT=`basename $2 .wav`
REAL_PATH=`realpath $0`
SCRIPT_DIR=`dirname $REAL_PATH`
IN_DIR=`dirname $1`
OUT_DIR=`dirname $2`
mkdir -p raw
$SCRIPT_DIR/wav2raw.sh "$1"
mv "$NAME_IN.raw" "raw/$NAME_IN.raw"
$SCRIPT_DIR/pipe.sh "raw/$NAME_IN.raw" "raw/$NAME_OUT.out.raw"
$SCRIPT_DIR/raw2wav.sh "raw/$NAME_OUT.out.raw"
mkdir -p "$OUT_DIR"
mv "$NAME_OUT.out.wav" "$2"
# rm -rf "raw"
