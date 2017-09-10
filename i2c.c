#include <stdio.h>
#include "i2c.h"
#include "MKL25Z4.h"

void i2c_write_byte(uint8_t data);

void i2c_sleep(uint8_t count){
	uint8_t i;

	for(i=0;i<count;i++){
		asm("nop");
	}
}

void init_i2c(){
	I2C0->F = 0x14;
	I2C0->C1 = I2C_C1_IICEN_MASK;
}


void i2c_start_xmit(uint8_t slave_id, uint8_t mode)
{
	slave_id = (slave_id << 1) | (mode & 0x1);
	
	i2c_Start();
	i2c_write_byte(slave_id);
}

static inline void i2c_wait(void){
	uint8_t i;

	while((I2C0->S & I2C_S_IICIF_MASK)==0); 

	I2C0->S |= I2C_S_IICIF_MASK;
}

inline uint8_t i2c_read_byte()
{
	uint8_t result;

	I2C0->C1 &= (~I2C_C1_TX_MASK);
	I2C0->C1 |= I2C_C1_TXAK_MASK;

	result = I2C0->D;
	i2c_wait();

	i2c_Stop();
	i2c_sleep(6);

	result = I2C0->D;
	return result;
}

static inline uint16_t i2c_read16()
{
	uint16_t result;

	I2C0->C1 &= (~I2C_C1_TX_MASK);
	I2C0->C1 &= (~I2C_C1_TXAK_MASK);

	result = I2C0->D; // dummy read for first transaction
	i2c_wait();
	
	I2C0->C1 |= I2C_C1_TXAK_MASK;
	result = I2C0->D << 8; // read in low high byte, transfer low byte
	i2c_wait();
	i2c_Stop();
	i2c_sleep(6);

	result |= I2C0->D; // read in low byte
	return result;
}

inline void i2c_write_byte(uint8_t data)
{
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 &= ~(I2C_C1_TXAK_MASK);
	I2C0->D = data;
}

uint8_t i2c_read_register(uint8_t slave_id,uint8_t reg_addr)
{
	uint8_t data;

	slave_id <<= 1;
	I2C0->S |= I2C_S_IICIF_MASK;

	i2c_Start();
	i2c_write_byte(slave_id | 0x0);
	i2c_wait();

	i2c_write_byte(reg_addr);
	i2c_wait();

	i2c_RepeatedStart();
	i2c_write_byte(slave_id | 0x1);
	i2c_wait();

	data = i2c_read_byte();

	return(data);
}

uint16_t i2c_read16_register(uint8_t slave_id,uint8_t reg_addr)
{
	uint16_t data;

	slave_id <<= 1;
	I2C0->S |= I2C_S_IICIF_MASK;

	i2c_Start();
	i2c_write_byte(slave_id | 0x0);
	i2c_wait();

	i2c_write_byte(reg_addr);
	i2c_wait();

	i2c_RepeatedStart();
	i2c_write_byte(slave_id | 0x1);
	i2c_wait();

	data = i2c_read16();

	return(data);
}

void i2c_write_register(uint8_t slave_id,uint8_t reg_addr,uint8_t data){

	slave_id <<= 1;
	I2C0->S |= I2C_S_IICIF_MASK;

	i2c_Start();
	i2c_write_byte(slave_id | 0x0);
	i2c_wait();

	i2c_write_byte(reg_addr);
	i2c_wait();

	i2c_write_byte(data);
	i2c_wait();

	i2c_Stop();
	i2c_sleep(6);
}
