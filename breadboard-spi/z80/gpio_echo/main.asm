start:
    call gpio_echo

end:
    jp PROMPT


gpio_echo:
    ; get a character from USB - will wait for a character
    call getchar
    ; escape?
    cp '\e'
    ; yes - end
    ret z
    ; echo to console
    call putchar
    ; send to SPI
    out (GPIO_OUT),a
    ; print a spacer
    ld a,' ' 
    call putchar
    ; wait
    call getchar
    ; read back from SPI
    in a,(GPIO_IN)
    ; stash value
    ld b,a
    ; print hex value
    call putchar_hex
    ; print a spacer
    ld a,' ' 
    call putchar
    ; restore value
    ld a,b
    ; print value
    call putchar
    ld a,'\n'
    call putchar
    ; repeat
    jr gpio_echo
