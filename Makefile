#PREFIX=arm-unknown-eabi
PREFIX=arm-none-eabi
FLAGS=-mcpu=cortex-m0plus -mthumb --specs=nosys.specs -DCMSIS  -fno-exceptions -g 
INC=-Ikl2xx/headers/CMSIS/MKL25Z4/Include -Icore/include 

CFLAGS=$(FLAGS) $(INC)
CXXFLAGS=$(FLAGS) $(INC) -fno-rtti

CC=$(PREFIX)-gcc
CXX=$(PREFIX)-g++
LD=$(PREFIX)-gcc

OBJS=test.o startup.o i2c.o mma8451.o tpm.o ws2812.o
KINETIS_OBJS=kl2xx/system_MKL25Z4.o 
LINKER_SCRIPTS=linker.ld

test.elf: $(OBJS) $(KINETIS_OBJS)
	$(LD) $(CFLAGS) -o $@ $^ -T $(LINKER_SCRIPTS) -Xlinker -Map=test.map

dump: test.elf
	$(PREFIX)-objdump -h $^
	#$(PREFIX)-readelf -S $^

debug: test.elf
	$(PREFIX)-gdb -ex "target remote | openocd -p -f board/frdm-kl25z.cfg" -ex "load" $^

clean:
	$(RM) *.o test.elf
	$(RM) kl2xx/*.o
