#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "circular_buffer.h"


void read_joystick(void* p) {
    int i = 0;
    while(1) {
        printf("Erik %d\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        ++i;
    }
}

void app_main(void)
{
    CircularBuffer buffer;
    init_circ_buff(&buffer);
    int16_t mean1 = mean_circ_buff(&buffer);
    printf("Mean: %d\n", mean1);
    //0
    for (int i = 0; i < (2 * BUFFER_LENGTH); i++) {
        add(&buffer, i);
    }
    int16_t mean2 = mean_circ_buff(&buffer);
    printf("Mean: %d\n", mean2);
    //30

    xTaskCreate(read_joystick, "read_joystick", 8000, NULL, 1, NULL);

}

//idf.py -p /dev/cu.SLAB_USBtoUART flash
//idf.py monitor