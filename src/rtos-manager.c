#include "rtos-manager.h"
#include "game-manager.h"

SemaphoreHandle_t x_mutex_for_var = NULL; // Create a mutex object

void rtos_init()
{

    x_mutex_for_var = xSemaphoreCreateMutex(); // crete a mutex object

    game_init();

    // pin the tasks

    xTaskCreatePinnedToCore(
        game_task,   // Function to implement the task
        "game_task", // Name of the task
        2000,        // Stack size in words
        NULL,        // Task input parameter
        10,          // Priority of the task
        NULL,        // Task handle.
        1            // Core where the task should run
    );
}
void rtos_manager() {}