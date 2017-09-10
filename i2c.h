#ifndef __I2C_H__
#define __I2C_H__

#define i2c_DisableAck()	I2C0->C1 |= I2C_C1_TXAK_MASK

#define i2c_RepeatedStart()	I2C0->C1 |= I2C_C1_RSTA_MASK;

#define i2c_Start()		I2C0->C1 |= I2C_C1_TX_MASK;\
				I2C0->C1 |= I2C_C1_MST_MASK

#define i2c_Stop()		I2C0->C1 &= ~I2C_C1_MST_MASK;\
				I2C0->C1 &= ~I2C_C1_TX_MASK

#define i2c_EnterRxMode()	I2C0->C1 &= ~I2C_C1_TX_MASK;\
				I2C0->C1 &= ~I2C_C1_TXAK_MASK

//#define i2c_Wait()		while((I2C0->S & I2C_S_IICIF_MASK)==0) {} \
//				I2C0->S |= I2C_S_IICIF_MASK;

//#define i2c_write_byte(data)	I2C0->D = (data)

#ifdef __cplusplus
extern "C" {
#endif
extern uint8_t i2c_read_register(uint8_t slave_id,uint8_t reg_addr);
extern uint8_t i2c_read_byte();
extern uint16_t i2c_read16_register(uint8_t slave_id,uint8_t reg_addr);
extern void i2c_write_register(uint8_t slave_id,uint8_t reg_addr,uint8_t data);
extern void init_i2c(void);

#ifdef __cplusplus
}
#endif

#endif // __I2C_H__
