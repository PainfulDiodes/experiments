; UM245R_CTRL                     = $0000 ; const, local, , beanboard, , asm/main.inc:13
; UM245R_DATA                     = $0001 ; const, local, , beanboard, , asm/main.inc:14
; 2-5 = keyboard
; GPIO_OUT    equ 6 ; either 6 or 7 will work
; GPIO_IN     equ 7 ; either 6 or 7 will work

CONTROL equ 0x08 ; control port (8 or 9 will work)

start:
    call test_loop

end:
    jp PROMPT


test_loop:
    call getchar
    cp '\e'
    ret z
    ld a,0
    out (CONTROL),a

    call getchar
    cp '\e'
    ret z
    ld a,1
    out (CONTROL),a

    call getchar
    cp '\e'
    ret z
    ld a,2
    out (CONTROL),a


    call getchar
    cp '\e'
    ret z
    ld a,3
    out (CONTROL),a

    jr test_loop
