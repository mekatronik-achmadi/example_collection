TARGET=wxserterm

CC=g++
INCDIR=-I./

OPT=-O0
WARN=-Wall
PTHREAD=-pthread

ifeq ($(OS),Windows_NT)
	CFLAGS=$(OPT) $(WARN) $(PTHREAD) -static $(shell wx-config-static --cppflags)
	LDFLAGS=$(OPT) $(WARN) $(PTHREAD) -static $(shell wx-config-static --libs)
else
	CFLAGS=$(OPT) $(WARN) $(PTHREAD) $(shell wx-config --cppflags)
	LDFLAGS=$(OPT) $(WARN) $(PTHREAD) $(shell wx-config --libs)
endif

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) *.plist *.exe

.PHONY: all clean
