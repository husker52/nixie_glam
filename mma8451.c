#include "mma8451.h"
#include "i2c.h"


uint16_t  mma8451_xval(){
      	return i2c_read16_register(MMA8451_ADDR,MMA8451_OUT_X_MSB);
}

uint16_t  mma8451_yval(){
       	return i2c_read16_register(MMA8451_ADDR,MMA8451_OUT_Y_MSB);
}

uint16_t  mma8451_zval(){
       	return i2c_read16_register(MMA8451_ADDR,MMA8451_OUT_Z_MSB);
}

uint8_t mma8451_status(){
       	return i2c_read_register(MMA8451_ADDR,MMA8451_STATUS);
}

uint8_t  mma8451_sysmode(){
       	return i2c_read_register(MMA8451_ADDR,MMA8451_SYSMOD);
}

uint8_t mma8451_whoami(){
       	i2c_read_register(MMA8451_ADDR,MMA8451_WHOAMI);
}

void mma8451_set_control(uint8_t val){
       	i2c_write_register(MMA8451_ADDR,MMA8451_CTRL_REG1,val);
}
