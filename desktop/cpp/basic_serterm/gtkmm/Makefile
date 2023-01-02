TARGET=gtkserterm

CC=g++
INCDIR=-I./ -I../ceSerial

OPT=-O0
WARN=-Wall
PTHREAD=-pthread

ifeq ($(OS),Windows_NT)
        CFLAGS=$(OPT) $(WARN) $(PTHREAD) -static $(shell pkg-config-static gtkmm-3.0 --cflags)
        LDFLAGS=$(OPT) $(WARN) $(PTHREAD) -static $(shell pkg-config-static gtkmm-3.0 --libs)
else
        CFLAGS=$(OPT) $(WARN) $(PTHREAD) $(shell pkg-config gtkmm-3.0 --cflags)
        LDFLAGS=$(OPT) $(WARN) $(PTHREAD) $(shell pkg-config gtkmm-3.0 --libs)
endif

SOURCES=main.cpp gtkserterm.cpp ../ceSerial/ceSerial.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) *.plist *.exe
	rm -f ../ceSerial/*.plist

.PHONY: all clean

