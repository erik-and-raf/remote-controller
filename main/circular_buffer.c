#include "circular_buffer.h"

void init_circ_buff(CircularBuffer* buffer) {
    for (uint8_t i = 0; i < BUFFER_LENGTH; i++) {
        buffer->buffer[i] = 0;
    }
    buffer->index = 0;
}

void add(CircularBuffer* buffer, uint16_t value) {
    buffer->buffer[buffer->index] = value;
    buffer->index = (buffer->index + 1) % BUFFER_LENGTH;
}

uint16_t mean_circ_buff(CircularBuffer* buffer) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < BUFFER_LENGTH; i++) {
        sum += buffer->buffer[i];
    }

    uint16_t average = sum/BUFFER_LENGTH;
    return average;
}