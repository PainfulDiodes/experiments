#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#define WAIT 14 // WAIT GP14     19
#define RST  15 // RST  GP15     20
#define MOSI 16 // MOSI GP16 RX  21
#define CS   17 // CS   GP17 CSn 22
#define SCK  18 // SCK  GP18 SCK 24
#define MISO 19 // MISO GP19 TX  25

// Buffer for captured GPIO values
#define GPIO_BUF_SIZE 1024
volatile uint8_t gpio_buffer[GPIO_BUF_SIZE];
volatile uint16_t gpio_buf_write_idx = 0;
volatile uint16_t gpio_buf_read_idx = 0;

void reset_callback(uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) {
        // Handle reset low event
        printf("Reset LOW\n");
    } else if (events & GPIO_IRQ_EDGE_RISE) {
        // Handle reset high event
        printf("Reset HIGH\n");
    }
}

void cs_callback() {
    uint8_t spi_ck, spi_rx, spi_tx, spi_cs, gpio_value, old_gpio_value, value, bitnum;
    old_gpio_value = 0;
    value = 0;
    bitnum = 7;
    
    do
    {
        spi_rx = gpio_get(MOSI);
        spi_cs = gpio_get(CS);
        spi_ck = gpio_get(SCK);
        spi_tx = gpio_get(MISO);
        gpio_value = (spi_tx << 3)|(spi_ck << 2)|(spi_cs << 1)|(spi_rx);
        if (gpio_value != old_gpio_value) {
            if(spi_ck) {
                value |= (spi_rx << bitnum--);
                if (bitnum==0) {
                    gpio_buffer[gpio_buf_write_idx++] = value;
                    value = 0;
                    bitnum = 7;
                }
            }
            old_gpio_value = gpio_value;
        }
    } while (!spi_cs);
}

// IRQ callback function
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == CS && (events & GPIO_IRQ_EDGE_FALL)) {
        cs_callback();
    }
    if (gpio == RST && (events & (GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL))) {
        reset_callback(events);
    }
}

int main() {
    stdio_init_all();
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);


    // Initialize GPIO
    for (uint pin = WAIT; pin <= MISO; pin++) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
    }

    // Set up falling edge interrupt for pin 17 (CS)
    gpio_set_irq_enabled_with_callback(CS, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(RST, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
        if (gpio_buf_read_idx != gpio_buf_write_idx)
            printf("\n");

        // Print all available captured values
        while (gpio_buf_read_idx != gpio_buf_write_idx) {
            printf("0x%02X ", gpio_buffer[gpio_buf_read_idx]);
            gpio_buf_read_idx = (gpio_buf_read_idx + 1) % GPIO_BUF_SIZE;
        }
    }
    return 0;
}