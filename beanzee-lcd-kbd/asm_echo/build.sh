# usage: 
#  ./build.sh

set -x #echo on

f="echo"
org=0x8000

z88dk-z80asm -l -m -s -b $f.asm
hexdump -C $f.bin > $f.hex
z88dk-appmake +hex --org $org -b $f.bin -o $f.ihx