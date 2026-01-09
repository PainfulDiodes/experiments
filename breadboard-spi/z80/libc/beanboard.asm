include "../lib/beanboard.asm"
include "../lib/extra.asm" ;definitions missing from beanboard.map because they are defined in marvin but not used there
include "marvin.asm"

PUBLIC marvin_lcd_putchar
PUBLIC _marvin_lcd_putchar

marvin_lcd_putchar:
_marvin_lcd_putchar:
    pop     bc      ;return address
    pop     hl      ;argument
    push    hl
    push    bc
    ld      a,l
    call    lcd_putchar
    ret

PUBLIC marvin_lcd_putcmd
PUBLIC _marvin_lcd_putcmd

marvin_lcd_putcmd:
_marvin_lcd_putcmd:
    pop     bc      ;return address
    pop     hl      ;argument
    push    hl
    push    bc
    ld      a,l
    call    lcd_putcmd
    ret

PUBLIC marvin_lcd_init
PUBLIC _marvin_lcd_init

marvin_lcd_init:
_marvin_lcd_init:
    call lcd_init
    ret

PUBLIC marvin_lcd_puts
PUBLIC _marvin_lcd_puts

marvin_lcd_puts:
_marvin_lcd_puts:
    pop     bc      ;return address
    pop     hl      ;argument
    push    hl
    push    bc
    call    lcd_puts ;print a zero-terminated string pointed to by hl to the LCD
    ret

PUBLIC marvin_gpio_in
PUBLIC _marvin_gpio_in

marvin_gpio_in:
_marvin_gpio_in:
    in a,(GPIO_IN)
    ld h,0
    ld l, a
    ret

PUBLIC marvin_gpio_out
PUBLIC _marvin_gpio_out

marvin_gpio_out:
_marvin_gpio_out:
    pop     bc      ; return address
    pop     hl      ; arg
    push    hl
    push    bc
    ld      a,l
    out (GPIO_OUT),a
    ret

PUBLIC marvin_keyscan_in
PUBLIC _marvin_keyscan_in

marvin_keyscan_in:
_marvin_keyscan_in:
    in a,(KEYSCAN_IN)
    ld h,0
    ld l, a
    ret

PUBLIC marvin_keyscan_out
PUBLIC _marvin_keyscan_out

marvin_keyscan_out:
_marvin_keyscan_out:
    pop     bc      ; return address
    pop     hl      ; arg
    push    hl
    push    bc
    ld      a,l
    out(KEYSCAN_OUT),a
    ret
