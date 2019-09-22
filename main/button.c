#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON_GPIO_PIN 4
#define ESP_INTR_FLAG_DEFAULT 0


void gpio_isr_handler() {
  ets_printf("hello", "I am logging\n");
}

void init_button() {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;
    io_conf.pin_bit_mask = 1ULL << BUTTON_GPIO_PIN;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(BUTTON_GPIO_PIN, gpio_isr_handler, NULL);
    gpio_set_intr_type(BUTTON_GPIO_PIN, GPIO_PIN_INTR_POSEDGE);
}