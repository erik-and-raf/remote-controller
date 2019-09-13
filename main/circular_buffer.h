#include <stdint.h>

#define BUFFER_LENGTH 20

typedef struct circ_buff_t {
    uint16_t buffer[BUFFER_LENGTH];
    uint8_t index;
} CircularBuffer;

void init_circ_buff(CircularBuffer* buffer); 

void add_circ_buff(CircularBuffer* buffer, uint16_t value); 

uint16_t mean_circ_buff(CircularBuffer* buffer); 

