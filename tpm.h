#ifndef __TPM_H__
#define __TPM_H__

#include "MKL25Z4.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

extern void tpm_init(uint8_t chan);
extern void tpm_program(void);
extern void tpm_test(void);
extern TPM_Type * tpm_type_delay(uint8_t chan);
extern void tpm_delayticks(TPM_Type *tpm,uint16_t ticks);
extern void tpm_type_pwm(uint8_t chan,uint8_t output,uint32_t per,uint32_t pwm);
extern void tpm_type_intr_enable(uint8_t chan);
#endif // __TPM_H__
