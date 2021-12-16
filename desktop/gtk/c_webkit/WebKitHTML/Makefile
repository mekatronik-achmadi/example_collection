# gcc -o tesweb main.c -pipe `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0` -export-dynamic

TARGET=docview
SRC=main.c

CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`
LIBS=`pkg-config --libs gtk+-3.0 webkit2gtk-4.0`
COPT=-Wall -pipe -export-dynamic

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LIBS) $(COPT)

