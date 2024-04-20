#ifndef __MY_PROGRAM__OLED_MANAGER_H__
#define __MY_PROGRAM__OLED_MANAGER_H__

#include "global.h"

#define CONFIG_I2C_INTERFACE
#define CONFIG_SDA_GPIO GPIO_NUM_21
#define CONFIG_SCL_GPIO GPIO_NUM_22
#define CONFIG_RESET_GPIO -1

#define TAG "OLED"
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#include "../lib/esp-idf-ssd1306/src/ssd1306.h"
#include "../lib/esp-idf-ssd1306/src/font8x8_basic.h"

void oled_init();
bool oled_clear();
bool oled_write_image(uint8_t x, uint8_t y, uint8_t *image, uint8_t width, uint8_t height, bool clear);
bool oled_write_text(uint8_t x, uint8_t y, char *text, uint8_t len, bool clear);

#endif
