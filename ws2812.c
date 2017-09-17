#include "ws2812.h"
#include "tpm.h"

#define NUM_LEDS 2
#define LEDBUF_LEN 3*NUM_LEDS

uint8_t ledbuf[LEDBUF_LEN] = {0,0,0,0xff,0x00,0x00};
uint8_t ledbit = 0;
uint16_t led_ptr = 0;
uint8_t led_lat = 0;
uint8_t led_current = 0;

void ws2812_init(void){
	tpm_type_pwm(1,0,96,96);
	//tpm_type_outcmp(1,0,96,96);
	tpm_type_intr_enable(1);
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

void ws2812_test(void){
	static uint8_t lednum = 0;

	switch(lednum){
		case 0:
		case 1:
			ledbuf[lednum] += 64;
			if( ledbuf[lednum] == 0){
				lednum++;
				ledbuf[lednum] += 64;
			}
			break;
		case 2:
			ledbuf[lednum] += 64;
			if( ledbuf[lednum] == 0){
				lednum = 0;
				ledbuf[lednum] += 64;
			}
			break;

	};

}

typedef struct {
	uint8_t r,g,b;
}LEDVAL;

void TPM1_IRQHandler(void){

	TPM1->SC |= TPM_SC_TOF_MASK;

	if(led_lat > 0){
		led_lat--;
		TPM1->CONTROLS[0].CnV = 0;
	}
	else{
		//TPM1->CONTROLS[0].CnV = led_current & 0x80 ? 34 : 11;
		TPM1->CONTROLS[0].CnV = led_current & 0x80 ? 60 : 11;

		led_current <<= 1;
		ledbit++;
		if(ledbit > 7){
			ledbit = 0;
			led_ptr++;
			if(led_ptr >= LEDBUF_LEN){
				led_ptr = 0;
				led_lat = 40;
			}
			led_current = ledbuf[led_ptr];
		}
	}
}
