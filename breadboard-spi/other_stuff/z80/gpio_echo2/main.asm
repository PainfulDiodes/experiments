start:
    call gpio_echo

end:
    jp PROMPT


gpio_echo:
    ld hl,input_buffer
    call getchar
    cp '\e'
    ret z
    call putchar
    ld (hl),a
    inc hl
    call getchar
    cp '\e'
    ret z
    call putchar
    ld (hl),a
    ld hl,input_buffer
    call hex_byte_val
    out (GPIO_OUT),a
    ld a,' ' 
    call putchar
    call getchar ; wait
    in a,(GPIO_IN)
    call putchar_hex
    ld a,'\n'
    call putchar
    jr gpio_echo

input_buffer:
    db 0,0
