#include "ht16k33.h"

// Low1 High1 Low2 High2 ... Low8 High8
uint8_t _buffer[16];
uint8_t _big_buffer[MAX_BIG_BUFFER_SIZE];
uint16_t _cursor_start, _cursor_end, _cursor_steps;
uint16_t _ms;
orientation_type_t _orientation;
int8_t _offset_x, _offset_y;
