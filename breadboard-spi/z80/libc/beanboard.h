void marvin_lcd_putcmd(char);
void marvin_lcd_putchar(char);
void marvin_lcd_init(void);
void marvin_lcd_puts(char *str);

char marvin_gpio_in(void);
void marvin_gpio_out(char);
char marvin_keyscan_in(void);
void marvin_keyscan_out(char);

#define LCD_BLINK_ON                    0x01
#define LCD_CLEAR_DISPLAY               0x01
#define LCD_CTRL                        0x04
#define LCD_CURSOR_ON                   0x02
#define LCD_DATA                        0x05
#define LCD_DATA_LEN_8                  0x10
#define LCD_DISPLAY_ON                  0x04
#define LCD_DISPLAY_ON_OFF_CONTROL      0x08
#define LCD_DISP_LINES_2                0x08
#define LCD_EOL_3                       0x67
#define LCD_FONT_8                      0x00
#define LCD_FUNCTION_SET                0x20
#define LCD_LINE_0_ADDR                 0x00
#define LCD_LINE_1_ADDR                 0x40
#define LCD_LINE_2_ADDR                 0x14
#define LCD_LINE_3_ADDR                 0x54
#define LCD_LINE_LEN                    0x14
#define LCD_NUM_LINES                   0x04
#define LCD_SET_DDRAM_ADDR              0x80
