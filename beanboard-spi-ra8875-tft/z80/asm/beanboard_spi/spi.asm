; Pin definitions for SPI on GPIO port

; GPO
; Serial Clock
SPI_SCK        equ 0
; Master Out Slave In
SPI_MOSI       equ 1
; RA8875 RESET - active LOW
RA8875_RESET   equ 2
; Chip Select - active LOW
SPI_CS         equ 3

; GPI
; WAIT
RA8875_WAIT    equ 0
; Master In Slave Out
SPI_MISO       equ 1

GPO_RESET_STATE equ 1 << SPI_CS
GPO_INIT_STATE equ 1 << SPI_CS | 1 << RA8875_RESET
GPO_SELECT_STATE equ 1 << RA8875_RESET
GPO_LOW_STATE equ 1 << RA8875_RESET
GPO_HIGH_STATE equ 1 << SPI_MOSI | 1 << RA8875_RESET

; Reset state
; Destroys: AF
spi_reset:
    ; Set initial pin states (RESET high, CS high, CLK low, MOSI low)
    ld a,GPO_RESET_STATE
    out (GPIO_OUT),a
    ret

; Initial state
; Prepare GPIO pins for SPI operation
; Destroys: AF
spi_init:
    ; Set initial pin states (RESET high, CS high, CLK low, MOSI low)
    ld a,GPO_INIT_STATE
    out (GPIO_OUT),a
    ret

; Select SPI device (CS low)
; Destroys: AF
spi_select:
    ; CS low
    ld a,GPO_SELECT_STATE
    out (GPIO_OUT),a
    ret

; Deselect SPI device (CS high)
; Destroys: AF
spi_deselect:
    ; CS high
    ld a,GPO_INIT_STATE
    out (GPIO_OUT),a
    ret

; Write a byte over SPI (no readback)
; Input: A = byte to send
; Destroys: AF, B
spi_write:
    ld b,8
spi_write_bit:
    ; MSB into carry flag
    rlca
    ; stash A
    ld d,a
    ; default to MOSI low
    ld a,GPO_LOW_STATE
    jr nc,spi_write_mosi
    ld a,GPO_HIGH_STATE
spi_write_mosi:
    out (GPIO_OUT),a
    ; clock high
    or 1 << SPI_SCK
    out (GPIO_OUT),a
    ; clock low
    and ~(1 << SPI_SCK)
    out (GPIO_OUT),a
    ; restore A
    ld a,d
    djnz spi_write_bit
    ret

; Read a byte over SPI (receive from MISO)
; Sends a dummy byte (0x00) during the read
; Output: A = byte received
; Destroys: AF, B
spi_read:
    ; Initialize bit counter and received byte
    ld b,8
    ld a,0
spi_read_bit:
    ; Shift received bits left
    sla a
    ; stash A
    ld d,a
    ; Set initial low state
    ld a,GPO_LOW_STATE
    out (GPIO_OUT),a
    ; Set clock high
    or 1 << SPI_SCK
    out (GPIO_OUT),a
    ; Read MISO bit
    in a,(GPIO_IN)
    bit SPI_MISO,a
    jr z,spi_read_miso_low
    ; MISO high - set LSB
    ld a,d
    or 1
    jr spi_read_clock_low
spi_read_miso_low:
    ; MISO low - keep LSB clear
    ld a,d
spi_read_clock_low:
    ; Set clock low
    ld d,a
    ld a,GPO_LOW_STATE
    out (GPIO_OUT),a
    ; Restore received byte
    ld a,d
    djnz spi_read_bit
    ret

