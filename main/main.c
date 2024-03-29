#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "circular_buffer.h"
#include "potentiometer.h"
#include "uart_remote.h"
#include "sdkconfig.h"
#include "bluetooth.h"
#include "button.h"
#include "driver/gpio.h"

#define JOYSTICK_SAMPLE_PERIOD 20
#define SEND_JOYSTICK_SAMPLE_PERIOD 50 

void read_joystick(void* circ_buff) {
    CircularBuffer* buffer = (CircularBuffer*) circ_buff;
    while(1) {
        int joystick_reading = get_potentiometer_reading();
        add_circ_buff(buffer, joystick_reading);
        vTaskDelay(JOYSTICK_SAMPLE_PERIOD / portTICK_PERIOD_MS);
    }
}

void send_joystick_reading(void* circ_buff) {
    CircularBuffer* buffer = (CircularBuffer*) circ_buff;
    // Wait a bit to make sure that bluetooth is configured
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    // Wait till the circular buffer is completely filled before reading values
    vTaskDelay(JOYSTICK_SAMPLE_PERIOD * BUFFER_LENGTH / portTICK_PERIOD_MS);

    while(1) {
        uint16_t circ_buff_mean = mean_circ_buff(buffer);
        // printf("The mean is: %d\n", circ_buff_mean);
        send_bluetooth_reading(circ_buff_mean);
        vTaskDelay(SEND_JOYSTICK_SAMPLE_PERIOD / portTICK_PERIOD_MS); 
    }
}


void read_button() {
    while(1) {
        int level = gpio_get_level(4);
        printf("It is: %d\n", level);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    setup_adc();
    init_uart_config();
    CircularBuffer buffer;
    init_circ_buff(&buffer);
    init_bluetooth();
    init_button();

    xTaskCreate(read_joystick, "read_joystick", 8000, (void*) &buffer, 1, NULL);
    xTaskCreate(send_joystick_reading, "sending_joystick_reading", 8000, &buffer, 1, NULL);
    xTaskCreate(read_button, "read_button", 8000, NULL, 1, NULL);

}

//idf.py -p /dev/cu.SLAB_USBtoUART flash
//idf.py monitor