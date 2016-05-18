#!/bin/sh

TARGET="posix"

if [ ! -d $TRAMPOLINE_PATH/goil/templates/ ]
   then
       echo "hum, cannot find goil templates, please check your TRAMPOLINE_PATH env variable"
       exit 1
   fi
     
if [ ! $# -eq 1 ]
then
    echo "wrong numer of args"
    exit 1
else
    filenameoil=$1
    echo "creating Makefile for $filenameoil"
    base=$(basename $1 .oil)
    goil --target=$TARGET --templates=$TRAMPOLINE_PATH/goil/templates/ $filenameoil
    if [ "$?" = "0" ]
    then
	echo "done."
	exit 0
    else
	echo "error"
	exit 2
    fi

    echo "done."
fi
