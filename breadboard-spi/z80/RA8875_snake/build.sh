#!/usr/bin/env bash

# NOTE: custom build file to incorporate an additional asm file - need a better way to do this

restart=0x0010
f=beanboard
org=0x9000

zcc +z80 -clib=classic main.c ra8875.asm ../libc/$f.asm -pragma-define:CRT_ORG_CODE=$org -pragma-define:CRT_ON_EXIT=$restart -create-app -m -Cz--ihex -o=output/$f.bin
