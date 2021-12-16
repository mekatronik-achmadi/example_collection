CFLAGS+= -Wall -D__DEBUG -O2 -mtune=cortex-a8 -march=armv7-a
LDFLAGS+= -lprussdrv -lpthread
OBJDIR=obj
TARGET= blinkled

_DEPS =
DEPS = $(patsubst %,$(INCDIR_APP_LOADER)/%,$(_DEPS))

_OBJ = blinkled.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OBJDIR)/%.o: %.c $(DEPS)
	@mkdir -p obj
	gcc $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf *.bin *.map *.out *.obj $(OBJDIR)/ *~  $(INCDIR_APP_LOADER)/*~  $(TARGET)

pru:
	clpru --silicon_version=3 -o1 blinkled_pru.c -z /opt/pru-cc/example/am33x_pru.cmd -o PRU_tests.out -m PRU_tests.map
	hexpru /opt/pru-cc/bin.cmd PRU_tests.out
