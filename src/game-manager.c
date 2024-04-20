#include "game-manager.h"
#include "oled-manager.h"
#include "esp_random.h"

#define WORLD_WIDTH 8
#define WORLD_HEIGHT 16
#define WORLD_EXISTANCE ((uint8_t)'#')
#define WORLD_EMPTY ((uint8_t)'-')

// #define WORLD_WIDTH 64
// #define WORLD_HEIGHT 128
// #define WORLD_EXISTANCE ((uint8_t)1)
// #define WORLD_EMPTY ((uint8_t)0)
uint8_t world[WORLD_WIDTH][WORLD_HEIGHT], world_copy[WORLD_WIDTH][WORLD_HEIGHT];

bool world_init_random(uint8_t matrix[WORLD_WIDTH][WORLD_HEIGHT])
{
    for (uint8_t i = 0; i < WORLD_WIDTH; i++)
    {
        for (uint8_t j = 0; j < WORLD_HEIGHT; j++)
        {
            matrix[i][j] = (esp_random() % 10) < 5 ? WORLD_EXISTANCE : WORLD_EMPTY;
        }
    }
    return true;
}

uint8_t world_get_neighbors_count(uint8_t matrix[WORLD_WIDTH][WORLD_HEIGHT], int16_t i, int16_t j)
{
    uint8_t neighbors_count = 0, xx = 0, yy = 0;

    for (int16_t x = (i - 1); x < (i + 2); x++)
    {
        for (int16_t y = (j - 1); y < (j + 2); y++)
        {
            if (x == i && y == j)
                continue;

            xx = x;
            yy = y;
            if (x < 0)
                xx = WORLD_WIDTH - 1;
            if (x > WORLD_WIDTH - 1)
                xx = 0;

            if (y < 0)
                yy = WORLD_HEIGHT - 1;
            if (y > WORLD_HEIGHT - 1)
                yy = 0;

            if (matrix[xx][yy] == WORLD_EXISTANCE)
                neighbors_count++;

            // ESP_LOGI("test", "in check %d,%d", xx, yy);
        }
    }
    return neighbors_count;
}

void world_step(uint8_t matrix[WORLD_WIDTH][WORLD_HEIGHT])
{

    // memcpy(world_copy, matrix, sizeof(world_copy));

    for (int16_t i = 0; i < WORLD_WIDTH; i++)
    {
        for (int16_t j = 0; j < WORLD_HEIGHT; j++)
        {
            // ESP_LOGI("test", "start of count %d,%d", i, j);
            uint8_t neighbors_count = world_get_neighbors_count(matrix, i, j);
            // ESP_LOGI("test", "end of count");

            if (matrix[i][j] == WORLD_EXISTANCE)
            {
                if (neighbors_count < 2 || neighbors_count > 3)
                    world_copy[i][j] = WORLD_EMPTY;
            }
            else
            {
                if (neighbors_count == 3)
                    world_copy[i][j] = WORLD_EXISTANCE;
            }

            // ESP_LOGI("test", "end of all");
        }
    }

    // for (uint8_t i = 0; i < OLED_WIDTH; i++)
    // {
    //     for (uint8_t j = 0; j < OLED_HEIGHT; j++)
    //     {
    //         matrix[i][j] = world_copy[i][j];
    //     }
    // }

    memcpy(matrix, world_copy, sizeof(world_copy));
}

void world_update_oled(uint8_t matrix[WORLD_WIDTH][WORLD_HEIGHT])
{
    // oled_write_image(0, 0, (uint8_t *)matrix, OLED_WIDTH, OLED_HEIGHT, true);
    for (uint8_t i = 0; i < 8; i++)
    {
        oled_write_text(i, 0, (char *)matrix[i], 16, i == 0);
    }
}

void game_init()
{
    memset(world, 0, sizeof(world));
    memset(world_copy, 0, sizeof(world_copy));

    world_init_random(world);
    memcpy(world_copy, world, sizeof(world_copy));

    world_update_oled(world);
}

void game_manager()
{
    world_step(world);
    world_update_oled(world);
    vTaskDelay(500 / portTICK_PERIOD_MS);
}

void game_task()
{
    ESP_LOGI("game", "core => %d", xPortGetCoreID());
    while (1)
    {
        game_manager();
    }
}