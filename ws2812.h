#ifndef _WS2812_H_
#define _WS2812_H_
#include <stdint.h>

extern void ws2812_init(void);
extern void ws2812_latch(void);
extern void ws2812_write(uint8_t *data, uint16_t len);
extern void ws2812_byte_write(uint8_t byte);
#endif // _WS2812_H_
