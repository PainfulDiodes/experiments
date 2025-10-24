#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>

int main() {
    stdio_init_all();

    // Set up SPI0 pins (default: SCK=18, MOSI=19, MISO=16, CS=17)
    gpio_set_function(16, GPIO_FUNC_SPI); // MISO
    gpio_set_function(17, GPIO_FUNC_SPI); // CSn
    gpio_set_function(18, GPIO_FUNC_SPI); // SCK
    gpio_set_function(19, GPIO_FUNC_SPI); // MOSI

    // Initialize SPI0 at any frequency (ignored in slave mode)
    spi_init(spi0, 1000 * 1000);

    // Set SPI format: 8 bits per transfer, CPOL=0 (clock idle low), CPHA=0 (data captured on first clock edge), MSB first
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    // Enable slave mode
    spi_set_slave(spi0, true);

    uint8_t rx_buf[32];
    while (true) {
        // Wait for data from master
        for (int i = 0; i < 32; ++i) {
            spi_read_blocking(spi0, 0, &rx_buf[i], 1);
            //printf("0x%02X ", rx_buf[i]);
            putchar(rx_buf[i]);
        }
    }
}