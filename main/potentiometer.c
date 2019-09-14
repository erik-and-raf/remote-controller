#include <driver/adc.h>

#define JOYSTICK_PIN ADC1_CHANNEL_6

void setup_adc() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(JOYSTICK_PIN, ADC_ATTEN_DB_11);
}

int get_potentiometer_reading() {
    return adc1_get_raw(JOYSTICK_PIN);
}