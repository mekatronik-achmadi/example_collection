include ../sinc/sinc.mk

APP = sin

CC = gcc
CCFLAGS = -Wall
CCLIBS = -lm

INC  = $(SINCINC)
SRC  = main.c $(SINCSRC)

COBJ = $(SRC:.c=.o)
OBJ  = $(wildcard *.o)

all: $(COBJ)
	$(CC) $(OBJ) -o $(APP) $(CCLIBS)

$(COBJ): %.o: %.c
	$(CC) $(CCFLAGS) -I$(INC) -c $<

clean:
	rm -f *.o $(APP)

.PHONY: clean all

