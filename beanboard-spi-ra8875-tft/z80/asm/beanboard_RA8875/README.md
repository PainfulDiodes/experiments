# BeanBoard RA8875
# Intro
- Assembled with z88dk-z80asm  
- Tested on BeanBoard v1, BeanZee v1 and Marvin v1.2.1-beanboard, Adafruit RA8875 controller, Adafruit 800x480 TFT panel
- RA8875 driver written in Z80 assembly
- Demonstrates SPI communication via bit-banged GPIO
- Hardware-specific example for BeanZee, BeanBoard, Adafruit RA8875 controller and TFT panel

## Hardware Requirements
- BeanBoard v1 expansion board
- Adafruit RA8875 TFT LCD controller module
- 800x480 resolution Adafruit TFT display
- SPI connection via GPIO pins:
  - GPO0: Serial Clock (SCK)
  - GPO1: Master Out Slave In (MOSI)
  - GPO2: Reset (active low)
  - GPO3: Chip Select (active low)
  - GPI1: Master In Slave Out (MISO)

## Features Demonstrated

### Low-Level SPI Communication
- Bit-banged SPI implementation using GPIO ports
- Hardware reset sequence
- Read/write operations over SPI
- Timing delays for RA8875 initialization

### RA8875 Controller Initialization
- Controller initialisation based on the Adafruit CPP library for the RA8875

### Register Access
- Reading from RA8875 registers
- Writing to RA8875 registers
- Controller presence detection (register 0 validation)
- Register dump functionality for debugging

### Text Mode Operations
- Switching to text mode
- Internal ROM font selection (8x16 character set)
- Cursor visibility and positioning
- Cursor blink control with configurable rate
- Character output (putchar)
- String output (puts)

## Example Program Flow
1. Initialize RA8875 controller (with error checking at each stage)
2. Configure for text mode with blinking cursor
3. Dump all 256 registers to console for debugging/verification
4. Display all characters (0-255) to test font rendering
5. Test precise cursor positioning:
   - Place 'X' at bottom-right corner (800-8, 480-16)
   - Place 'X' at character position (10, 10)
   - Place 'X' at a mid-character offset (10*8+4, 10*16)
6. Reset cursor to origin (0, 0)
7. Display "Hello, world!" message - overwrites the originally displayed text
8. Return to Marvin monitor

## Code Architecture

### RA8875.asm Library Structure
- Constants and register definitions (based on datasheet)
- Low-level SPI primitives (_ra8875_write, _ra8875_read)
- Basic RA8875 commands (command/data read/write)
- Register access routines
- Initialization functions (modular, per-subsystem)
- High-level text mode functions

## Usage Notes
- Requires BeanBoard hardware with RA8875 module connected
- Build with `./build.sh beanboard`
- Load output/beanboard.ihx to BeanZee
- Execute with `x8000` from Marvin monitor
- Console shows register dump for verification
- Display shows all characters plus test message

