#include "usb.h"
#include <stdint.h>

__attribute__((aligned(512))) struct bdt_st {
	uint32_t config;
 	uint8_t *addr;
} bdt[64];

uint8_t bd[4*512];

void USB0_IRQHandler(void){
	uint32_t temp;

	temp = USB0->ISTAT;

	USB0->ISTAT = temp;
}

void usb_init(void){
	uint16_t i;
	uint32_t addr;

	addr = (uint32_t )&bdt;

	SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;

	USB0->BDTPAGE1 = (addr >> 8);
	USB0->BDTPAGE2 = (addr >> 16);
	USB0->BDTPAGE3 = (addr >> 24);


	for(i=0;i<4;i++){
		bdt[i].addr = &bd[i*512];
	}
	USB0->INTEN = (USB_INTEN_USBRSTEN_MASK | USB_INTEN_ATTACHEN_MASK);
	USB0->CTL = (USB_CTL_USBENSOFEN_MASK | USB_CTL_RESET_MASK);
}

