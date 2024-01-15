# target name
TARGET=appname

# compiler binary
CC=valac

# source directories
SRCDIR=./

# gui resource
GUIRC=main.glade

# build output directory
ODIR=build

# compiler options
COPT=-O0 -Wall -pthread -rdynamic
FLAGS=--pkg gtk+-3.0 --pkg gmodule-2.0


################### Non Configurable ########################

SRC=$(wildcard $(SRCDIR)/*.vala)

all: dir $(ODIR)/$(TARGET)

dir:
	mkdir -p $(ODIR)

$(ODIR)/$(TARGET): $(SRC) $(GUIRC)
	cp -vf $(GUIRC) $(ODIR)/$(GUIRC)
	$(CC) $(FLAGS) -o $(ODIR)/$(TARGET) $(SRC)

clean:
	rm -rf $(ODIR)/

.PHONY: all dir clean

