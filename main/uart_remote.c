#include <driver/uart.h>
#include <esp_err.h>
#include <string.h>
#include <driver/gpio.h>

#define UART_NUM UART_NUM_2
#define TRANSMITTER_PIN GPIO_NUM_4
#define RECEIVER_PIN GPIO_NUM_5


void init_uart_config() {
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, TRANSMITTER_PIN, RECEIVER_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    // Change to ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024);
    // QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, uart_buffer_size * 2, \
                                            0, 0, NULL, 0));

}

void send_uart(uint16_t uart_reading) {
    char buffer[2];
    buffer[0] = uart_reading & 0xFF;
    buffer[1] = uart_reading >> 8;
    int written_bytes = uart_write_bytes(UART_NUM_1, (const char* ) buffer, 2);
    printf("Bytes written: %d\n", written_bytes);
}
