#!/usr/bin/env bash

# Usage: ./build.sh target org
# E.g.:  ./build.sh beanboard 0x8000
# org is optional - defaults to 0x8000

# set -x #echo on

f=$1

if [[ $# -gt 1 ]]
then
    org=$2
else
    org=0x8000
fi

z88dk-z80asm -l -b -m -DORGDEF=$org $f.asm -Ooutput
hexdump -C output/$f.bin > output/$f.hex
z88dk-appmake +hex --org $org -b output/$f.bin -o output/$f.ihx
