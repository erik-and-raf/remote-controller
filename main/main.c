#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/adc.h>
#include "circular_buffer.h"

#define JOYSTICK_SAMPLE_PERIOD 20
#define SEND_JOYSTICK_SAMPLE_PERIOD 250
#define JOYSTICK_PIN ADC1_CHANNEL_6

void read_joystick(void* circ_buff) {
    CircularBuffer* buffer = (CircularBuffer*) circ_buff;
    while(1) {
        int joystick_reading = adc1_get_raw(JOYSTICK_PIN);
        add_circ_buff(buffer, joystick_reading);
        vTaskDelay(JOYSTICK_SAMPLE_PERIOD / portTICK_PERIOD_MS);
    }
}

void send_joystick_reading(void* circ_buff) {
    CircularBuffer* buffer = (CircularBuffer*) circ_buff;

    // Wait till the circular buffer is completely filled before reading values
    vTaskDelay(JOYSTICK_SAMPLE_PERIOD * BUFFER_LENGTH / portTICK_PERIOD_MS);

    while(1) {
        uint16_t circ_buff_mean = mean_circ_buff(buffer);
        printf("The mean is: %d\n", circ_buff_mean);
        vTaskDelay(SEND_JOYSTICK_SAMPLE_PERIOD / portTICK_PERIOD_MS); 
    }
}

void app_main(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(JOYSTICK_PIN, ADC_ATTEN_DB_11);
    CircularBuffer buffer;
    init_circ_buff(&buffer);
    xTaskCreate(read_joystick, "read_joystick", 8000, (void*) &buffer, 1, NULL);
    xTaskCreate(send_joystick_reading, "sending_joystick_reading", 8000, &buffer, 1, NULL);
}

//idf.py -p /dev/cu.SLAB_USBtoUART flash
//idf.py monitor