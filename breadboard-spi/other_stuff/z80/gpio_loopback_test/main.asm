start:
    call ra8875_test

end:
    jp PROMPT


ra8875_test:
    ld a,0b00000000
    call ra8875_test_step
    ld a,0b00000001
    call ra8875_test_step
    ld a,0b00000010
    call ra8875_test_step
    ld a,0b00000100
    call ra8875_test_step
    ld a,0b00001000
    call ra8875_test_step
    ld a,0b00010000
    call ra8875_test_step
    ld a,0b00100000
    call ra8875_test_step
    ld a,0b01000000
    call ra8875_test_step
    ld a,0b10000000
    call ra8875_test_step
    ret

ra8875_test_step:
    out (GPIO_OUT),a
    call my_long_delay
    in a,(GPIO_IN)
    call putchar_hex
    ld a,'\n'
    call putchar
    ret

my_delay:
    push bc
    ld b,0xff
my_delay_loop:
    nop
    djnz my_delay_loop
    pop bc
    ret

my_long_delay: 
    push bc
    ld b,0xff
my_long_delay_loop: 
    call my_delay
    djnz my_long_delay_loop
    pop bc
ret
