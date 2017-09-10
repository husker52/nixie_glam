#ifndef _MMA8451_H
#define _MMA8451_H

#include <stdio.h>
#include "i2c.h"

#define MMA8451_ADDR 0x1d
//#define MMA8451_ADDR 0x55
#define MMA8451_SYSMOD 0x0b
#define MMA8451_WHOAMI 0x0d
#define MMA8451_STATUS 0x00
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_CTRL_REG1 0x2a

//#define mma8451_xval() i2c_read16_register(MMA8451_ADDR,MMA8451_OUT_X_MSB)
//#define mma8451_yval() i2c_read16_register(MMA8451_ADDR,MMA8451_OUT_Y_MSB)
//#define mma8451_zval() i2c_read16_register(MMA8451_ADDR,MMA8451_OUT_Z_MSB)
//#define mma8451_status() i2c_read_register(MMA8451_ADDR,MMA8451_STATUS)
//#define mma8451_sysmode() i2c_read_register(MMA8451_ADDR,MMA8451_SYSMOD)
//#define mma8451_whoami() i2c_read_register(MMA8451_ADDR,MMA8451_WHOAMI)
//#define mma8451_set_control(val) i2c_write_register(MMA8451_ADDR,MMA8451_CTRL_REG1,val)

extern uint16_t mma8451_xval(void); 
extern uint16_t mma8451_yval(void); 
extern uint16_t mma8451_zval(void); 
extern uint8_t mma8451_status(void); 
extern uint8_t mma8451_sysmode(void); 
extern uint8_t mma8451_whoami(void); 
extern void mma8451_set_control(uint8_t val);

#endif // _MMA8451_H
