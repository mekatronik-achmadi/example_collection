CC=gcc
PRU_ASM=pasm

all:
	@echo ">> Generating PRU binary"
	$(PRU_ASM) -b pru-hcsr04.p
	@echo ">> Compiling Sonar Example"
	$(CC) -o pru-hcsr04 pru-hcsr04.c -lpthread -lprussdrv
	
clean:
	rm -rf pru-hcsr04 pru-hcsr04.o pru-hcsr04.bin 
    
