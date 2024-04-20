#include "main.h"

void app_main()
{
    // variables

    // setup

    // non os inits
    oled_init();

    // rtos init
    rtos_init();

    // loop
    while (1)
    {
        /* code */
        ESP_LOGI("LOOP", "in loop");
        ESP_LOGI("loop", "core => %d", xPortGetCoreID());
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}