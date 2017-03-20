#!/bin/sh

if [ $# -ne 2 ]; then
	echo "Usage: ./pipe.sh [infile] [outfile]"
	exit
fi;

echo "Setting up UART..."
# set most options necessary for raw transmission:
#  raw
# disable all echo options to avoid forward feedback when listening
#  -echo -echoctl -echoe -echok -echoke -echonl -echoprt
# disable new line/carriage return translation during transmit
#  -onlcr -ocrnl 115200 

stty -F /dev/fsl-tty \
  -echo -echoctl -echoe -echok -echoke -echonl -echoprt \
  -onlcr -ocrnl 115200 \
  raw

echo "Preparing output pipe..."
cat /dev/fsl-tty > $2 &
CATIN=$!

echo "Beginning input pipe..."
cat $1 > /dev/fsl-tty
echo "Waiting for output to terminate..."
sleep 2
kill $CATIN
echo "All done."
