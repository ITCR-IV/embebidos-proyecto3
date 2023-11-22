#include "ht16k33.h"

// Low1 High1 Low2 High2 ... Low8 High8
uint8_t buffer[16];
// uint8_t big_buffer[MAX_BIG_BUFFER_SIZE];
uint16_t cursor_start, cursor_end, cursor_steps;
uint16_t ms;
// orientation_type_t orientation;
int8_t offset_x, offset_y;
