#!/usr/bin/env bash

# Usage: ./build.sh target org
# E.g.:  ./build.sh beanboard 0x8000
# org is optional - defaults to 0x8000

# set -x #echo on

restart=0x0010
f=$1

if [[ $# -gt 1 ]]
then
    org=$2
else
    org=0x8000
fi

zcc +z80 -clib=classic main.c ../lib/$f.asm -pragma-define:CRT_ORG_CODE=$org -pragma-define:CRT_ON_EXIT=$restart -create-app -m -Cz--ihex -o=output/$f.bin
z88dk-dis -o $org -x output/$f.map -x ../../lib/$f.map output/$f.bin >output/$f.dis