; Marvin 1.0.2-> definitions

; memory map
RAMSTART equ $8000
RAMTOP equ   $efff

; jp addresses
RESET equ $0000         ; cold start
START equ $0050         ; warm start

; subroutines to call
getchar equ $0010       ; get a character from the console and return in A
putchar equ $0020       ; send character in A to the console 
putc equ    $0030 
puts equ    $0040       ; print a zero-terminated string pointed to by HL to the console
