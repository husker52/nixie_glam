#include "ws2812.h"

void ws2812_init(void){

}

void ws2812_write(uint8_t *data, uint16_t len){
	uint16_t i;

	for(i=0;i<len;i++){
		ws2812_byte_write(data[i]);
	}
	ws2812_latch();
}

void ws2812_byte_write(uint8_t byte){

	uint8_t i;

	for(i=0;i<8;i++){
	
		if(byte & 0x80){

		}
		else{

		}
		byte <<= 1;
	}
}

void ws2812_latch(void){

}
