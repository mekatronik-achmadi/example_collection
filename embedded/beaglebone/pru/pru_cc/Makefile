CC = clpru
DEVICE=am335x
CFLAGS = --silicon_version=3 -o1 -D$(DEVICE)
HEXBIN = hexpru

INC_C_DIR = -I/opt/pru-cc/lib \
	    -I/opt/pru-cc/include \
	    -I/opt/pru-cc/am335x_starterware/include \
	    -I/opt/pru-cc/am335x_starterware/include/arm7a \
	    -I/opt/pru-cc/am335x_starterware/include/hw \
	    -I/opt/pru-cc/am335x_starterware/platform/beaglebone

DRIVER_DIR = /opt/pru-cc/am335x_starterware/drivers
SRC = $(wildcard ${DRIVER_DIR}/*.c) blinkled.c
OUT = blinkled.out
CMD = /opt/pru-cc/example/am33x_pru.cmd
BUILD_DIR = build

$(BUILD_DIR)/$(OUT):$(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_C_DIR) $^ -z $(CMD) -o $@ -m $(OUT).map
	rm -rf *.out *.map *.obj
	$(HEXBIN) /opt/pru-cc/bin.cmd $@
	cp *.bin $(BUILD_DIR)
	rm -rf *.bin
clean:
	rm -r build/
