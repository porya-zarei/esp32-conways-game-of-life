#include "oled-manager.h"

SSD1306_t oled;

bool oled_clear()
{
    ssd1306_clear_screen(&oled, false);
    return true;
}

bool oled_write_image(uint8_t x, uint8_t y, uint8_t *image, uint8_t width, uint8_t height, bool clear)
{
    if (clear)
        oled_clear();
    ssd1306_bitmaps(&oled, x, y, image, width, height, false);
    // ssd1306_display_image(&oled,0,0,image,width);
    return true;
}

bool oled_write_pixel(uint8_t x, uint8_t y, bool invert, bool clear)
{
    if (clear)
        oled_clear();
    ssd1306_pixel(&oled, x, y, invert);
    return true;
}

bool oled_write_text(uint8_t x, uint8_t y, char *text, uint8_t len, bool clear)
{
    if (clear)
        oled_clear();
    ssd1306_display_text(&oled, x, text, len, false);
    return true;
}

void oled_init()
{
    ESP_LOGI(TAG, "INTERFACE is i2c");
    ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
    ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
    ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
    i2c_master_init(&oled, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);

    ssd1306_init(&oled, OLED_WIDTH, OLED_HEIGHT);
    ssd1306_contrast(&oled, 0xff);

    oled_clear();

    oled_write_text(0, 0, "Hello World!", 13, true);
}
