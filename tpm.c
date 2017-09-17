#include <stdio.h>
#include "tpm.h"
#include "MKL25Z4.h"

void tpm_init(uint8_t chan){

	switch(chan){
		case 0:
			// turn on clock for TPM
			SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
			break;
		case 1:
			// turn on clock for TPM
			SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
			break;
		case 2:
			// turn on clock for TPM
			SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
			break;
		default:
			break;
	}
	// select processor PLL source
	SIM->SOPT2 |= (1 << SIM_SOPT2_PLLFLLSEL_SHIFT)|SIM_SOPT2_TPMSRC(1);
//	SIM->SOPT2 |= (2 << 24);
	//MCG->C5 |= (1 << MCG_C5_PLLSTEN0_SHIFT);


}

TPM_Type * tpm_type_delay(uint8_t chan){

	TPM_Type *tpm;

	switch(chan){
		case 0:
			tpm = TPM0;
			break;
		case 1:
			tpm = TPM1;
			break;
		case 2:
			tpm = TPM2;
			break;
		default:
			return NULL;
			break;
	}
	tpm->SC = TPM_SC_CMOD(1);
	tpm->MOD = 10; // aribtrary value, will be set by delay method 
	tpm->CONF = 0;
	return tpm;
}

void tpm_delayticks(TPM_Type *tpm,uint16_t ticks){

	if(tpm == NULL)
		return;
	tpm->STATUS = TPM_STATUS_TOF_MASK;
	tpm->MOD = ticks;
	tpm->CNT = 0;
	while((tpm->STATUS & TPM_STATUS_TOF_MASK) == 0){
		asm("	nop");
	}
}

void tpm_type_pwm(uint8_t chan,uint8_t output,uint32_t per,uint32_t pwm){

	TPM_Type *tpm;

	switch(chan){
		case 0:
			tpm = TPM0;
			break;
		case 1:
			tpm = TPM1;
			break;
		case 2:
			tpm = TPM2;
			break;
		default:
			return;
			break;
	}
	tpm->SC = TPM_SC_CMOD(1);
	tpm->MOD = per; 
	tpm->CONTROLS[output].CnSC = (2 << TPM_CnSC_ELSA_SHIFT)|(2 << TPM_CnSC_MSA_SHIFT);
	tpm->CONTROLS[output].CnV = pwm;
	tpm->CONF = 0;
}

void tpm_type_outcmp(uint8_t chan,uint8_t output,uint32_t per,uint32_t pwm){

	TPM_Type *tpm;

	switch(chan){
		case 0:
			tpm = TPM0;
			break;
		case 1:
			tpm = TPM1;
			break;
		case 2:
			tpm = TPM2;
			break;
		default:
			return;
			break;
	}
	tpm->SC = TPM_SC_CMOD(1);
	tpm->MOD = per; 
	tpm->CONTROLS[output].CnSC = (2 << TPM_CnSC_ELSA_SHIFT)|(1 << TPM_CnSC_MSA_SHIFT);
	tpm->CONTROLS[output].CnV = pwm;
	tpm->CONF = 0;
}


void tpm_type_intr_enable(uint8_t chan){

	TPM_Type *tpm;
	switch(chan){
		case 0:
			tpm = TPM0;
			break;
		case 1:
			tpm = TPM1;
			break;
		case 2:
			tpm = TPM2;
			break;
		default:
			return;
			break;
	}
	tpm->SC |= TPM_SC_TOIE_MASK | TPM_SC_TOF_MASK;
	NVIC_EnableIRQ(TPM1_IRQn);
}


void tpm_program(void){
	TPM1->SC = TPM_SC_CMOD(1);
	TPM1->MOD = 13; // 82;
	TPM1->CONTROLS[0].CnSC = (2 << TPM_CnSC_ELSA_SHIFT)|(2 << TPM_CnSC_MSA_SHIFT);
	TPM1->CONTROLS[0].CnV = 11;// 65;
	TPM1->CONF = 17;
}

void tpm_test(void){
	FPTE->PTOR = (0x1 << 20);
}
