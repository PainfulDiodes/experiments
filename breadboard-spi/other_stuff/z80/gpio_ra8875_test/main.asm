start:
    call ra8875_test
    ld a,'\n'
    call putchar

end:
    jp PROMPT


ra8875_test:
    ld a,0x80
    out (GPIO_OUT),a
    call my_delay
    in a,(GPIO_IN)
    call putchar_hex
    ld a,0x00
    out (GPIO_OUT),a
    call my_delay
    in a,(GPIO_IN)
    call putchar_hex
    ld a,0x40
    out (GPIO_OUT),a
    call my_delay
    in a,(GPIO_IN)
    call putchar_hex
    ld a,0x00
    out (GPIO_OUT),a
    call my_delay
    in a,(GPIO_IN)
    call putchar_hex
    ret


my_delay:
    push bc
    ld b,0x40
my_delay_loop:
    nop
    djnz my_delay_loop
    pop bc
    ret
