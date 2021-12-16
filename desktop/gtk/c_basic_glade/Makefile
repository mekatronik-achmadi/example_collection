all: test
	
test: main.c
	gcc -Wall -g -o test main.c $(pkg-config --cflags --libs gtk+-2.0 gmodule-2.0)
