RA8875_DATAWRITE equ 0x00
RA8875_DATAREAD equ 0x40
RA8875_CMDWRITE equ 0x80
RA8875_CMDREAD equ 0xC0

start:
    call spi_reset
    ld hl,message
    call puts
    call getchar
    call spi_init

send_loop:
    call getchar
    cp '\e'
    jp z,done
    call putchar
    push af
    ld a, ' '
    call putchar
    call spi_select
    pop af
    call spi_write
    call spi_deselect
    call spi_select
    call spi_read
    call putchar_hex
    call spi_deselect
    ld a,'\n'
    call putchar
    jr send_loop
done:
    jp WARMSTART

message:
    db "SPI test\nHit any key to continue...\n",0
