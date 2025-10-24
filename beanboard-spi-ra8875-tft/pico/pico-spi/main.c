// Skeleton Raspberry Pi Pico 2 W project
// Uses USB console and GPIO

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>


// Buffer for captured GPIO values
#define GPIO_BUF_SIZE 1024
volatile uint8_t gpio_buffer[GPIO_BUF_SIZE];
volatile uint16_t gpio_buf_write_idx = 0;
volatile uint16_t gpio_buf_read_idx = 0;

// IRQ callback function
void gpio_callback(uint gpio, uint32_t events) {
    // SPI0 RX  / GP16 (21) = 1
    // SPI0 CSn / GP17 (22) = 2
    // SPI0 SCK / GP18 (24) = 4
    // SPI0 TX  / GP19 (25) = 8
    uint8_t spi_ck, spi_rx, spi_tx, spi_cs, value, oldvalue;
    oldvalue = 0;
    do
    {
        value = 0;
        spi_rx = gpio_get(16);
        spi_cs = gpio_get(17);
        spi_ck = gpio_get(18);
        spi_tx = gpio_get(19);
        value = (spi_tx << 3)|(spi_ck << 2)|(spi_cs << 1)|(spi_rx);
        if (value != oldvalue) {
            gpio_buffer[gpio_buf_write_idx++] = value;
            if (gpio_buf_write_idx >= GPIO_BUF_SIZE) {
                gpio_buf_write_idx = 0;
            }
            oldvalue = value;
        }
    } while (!spi_cs);
}

int main() {
    stdio_init_all();
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);


    // Initialize GPIO
    for (uint pin = 16; pin <= 19; pin++) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
    }

    // Set up falling edge interrupt for pin 17 (CS)
    gpio_set_irq_enabled_with_callback(17, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
        printf("\n");

        // Print all available captured values
        while (gpio_buf_read_idx != gpio_buf_write_idx) {
            printf("0x%02X ", gpio_buffer[gpio_buf_read_idx]);
            gpio_buf_read_idx = (gpio_buf_read_idx + 1) % GPIO_BUF_SIZE;
        }
    }
    return 0;
}