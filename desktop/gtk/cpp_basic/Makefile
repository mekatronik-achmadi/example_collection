CC=g++
CFLAGS= -v -c -Wall
SOURCES=hw.cpp main.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXEC=myhw

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ `pkg-config gtkmm-3.0 --libs`

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ `pkg-config gtkmm-3.0 --cflags`

clean:
	rm -rf *.o $(EXEC)
