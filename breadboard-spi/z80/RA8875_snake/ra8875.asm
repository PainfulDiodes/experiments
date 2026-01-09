ra8875_adafruit_tft_enable      = $82AD ; addr, local, , beanboard, , RA8875.asm:376
ra8875_backlight_init           = $82B9 ; addr, local, , beanboard, , RA8875.asm:387
ra8875_clear_window             = $828E ; addr, local, , beanboard, , RA8875.asm:350
ra8875_controller_error         = $804D ; addr, local, , beanboard, , main.asm:45
ra8875_controller_error_message = $80ED ; addr, local, , beanboard, , main.asm:154
ra8875_cursor_blink             = $8322 ; addr, local, , beanboard, , RA8875.asm:457
ra8875_cursor_off               = $834B ; addr, local, , beanboard, , RA8875.asm:481
ra8875_cursor_x                 = $835B ; addr, local, , beanboard, , RA8875.asm:492
ra8875_cursor_y                 = $8372 ; addr, local, , beanboard, , RA8875.asm:508
ra8875_delay                    = $810A ; addr, local, , beanboard, , RA8875.asm:30
ra8875_deselect                 = $8143 ; addr, local, , beanboard, , RA8875.asm:102
ra8875_display_on               = $82A1 ; addr, local, , beanboard, , RA8875.asm:365
ra8875_hardware_spi_end         = $8035 ; addr, local, , beanboard, , main.asm:29
ra8875_hardware_spi_start       = $8000 ; addr, local, , beanboard, , main.asm:1
ra8875_horizontal_active_window_init = $824C ; addr, local, , beanboard, , RA8875.asm:312
ra8875_horizontal_settings_init = $81EE ; addr, local, , beanboard, , RA8875.asm:262
ra8875_init_delay               = $8132 ; addr, local, , beanboard, , RA8875.asm:81
ra8875_initialise               = $82CC ; addr, local, , beanboard, , RA8875.asm:404
ra8875_memory_read_write_command = $8389 ; addr, local, , beanboard, , RA8875.asm:523
ra8875_pcsr_init                = $81DF ; addr, local, , beanboard, , RA8875.asm:251
ra8875_pllc1_init               = $81B5 ; addr, local, , beanboard, , RA8875.asm:219
ra8875_pllc2_init               = $81C4 ; addr, local, , beanboard, , RA8875.asm:230
ra8875_putchar                  = $8391 ; addr, local, , beanboard, , RA8875.asm:531
ra8875_puts                     = $83A0 ; addr, local, , beanboard, , RA8875.asm:545
ra8875_read_data                = $818B ; addr, local, , beanboard, , RA8875.asm:175
ra8875_read_reg                 = $819C ; addr, local, , beanboard, , RA8875.asm:191
ra8875_reg_0_check              = $81AD ; addr, local, , beanboard, , RA8875.asm:213
ra8875_reset                    = $814A ; addr, local, , beanboard, , RA8875.asm:109
ra8875_reset_delay              = $8112 ; addr, local, , beanboard, , RA8875.asm:37
ra8875_select                   = $813C ; addr, local, , beanboard, , RA8875.asm:95
ra8875_setup                    = $8038 ; addr, local, , beanboard, , main.asm:32
ra8875_sysr_init                = $81D3 ; addr, local, , beanboard, , RA8875.asm:241
ra8875_text_mode                = $8305 ; addr, local, , beanboard, , RA8875.asm:438
ra8875_vertical_active_window_init = $826D ; addr, local, , beanboard, , RA8875.asm:331
ra8875_vertical_settings_init   = $8216 ; addr, local, , beanboard, , RA8875.asm:284
ra8875_write_command            = $8161 ; addr, local, , beanboard, , RA8875.asm:143
ra8875_write_data               = $8176 ; addr, local, , beanboard, , RA8875.asm:159
ra8875_write_reg                = $81A3 ; addr, local, , beanboard, , RA8875.asm:198
test_cursor_positioning         = $80B5 ; addr, local, , beanboard, , main.asm:122
test_fill_screen                = $808B ; addr, local, , beanboard, , main.asm:94
test_fill_screen_fast           = $80A0 ; addr, local, , beanboard, , main.asm:108
test_message                    = $80FC ; addr, local, , beanboard, , main.asm:157
test_print_all_chars            = $806E ; addr, local, , beanboard, , main.asm:71
test_print_all_chars_fast       = $807B ; addr, local, , beanboard, , main.asm:82


PUBLIC tft_setup
PUBLIC _tft_setup

tft_setup:
_tft_setup:
    call ra8875_setup
    ret

PUBLIC tft_clear_screen
PUBLIC _tft_clear_screen

tft_clear_screen:
_tft_clear_screen:
    call ra8875_clear_window
    ret

PUBLIC tft_cursor_on
PUBLIC _tft_cursor_on

tft_cursor_on:
_tft_cursor_on:
    call ra8875_cursor_blink
    ret

PUBLIC tft_cursor_off
PUBLIC _tft_cursor_off

tft_cursor_off:
_tft_cursor_off:
    call ra8875_cursor_off
    ret

PUBLIC tft_cursor_x
PUBLIC _tft_cursor_x

tft_cursor_x:
_tft_cursor_x:
    pop     bc      ; return address
    pop     hl      ; arg
    push    hl
    push    bc
    call ra8875_cursor_x ; expects hl to have x position
    ret

PUBLIC tft_cursor_y
PUBLIC _tft_cursor_y

tft_cursor_y:
_tft_cursor_y:
    pop     bc      ; return address
    pop     hl      ; arg
    push    hl
    push    bc
    call ra8875_cursor_y ; expects hl to have y position
    ret

PUBLIC tft_putchar
PUBLIC _tft_putchar

tft_putchar:
_tft_putchar:
    pop     bc      ; return address
    pop     hl      ; arg
    push    hl
    push    bc
    ld a,l
    call ra8875_putchar
    ret

; PUBLIC marvin_gpio_in
; PUBLIC _marvin_gpio_in

; marvin_gpio_in:
; _marvin_gpio_in:
;     in a,(GPIO_IN)
;     ld h,0
;     ld l, a
;     ret

; PUBLIC marvin_gpio_out
; PUBLIC _marvin_gpio_out

; marvin_gpio_out:
; _marvin_gpio_out:
;     pop     bc      ; return address
;     pop     hl      ; arg
;     push    hl
;     push    bc
;     ld      a,l
;     out (GPIO_OUT),a
;     ret
