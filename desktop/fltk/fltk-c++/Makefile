# target name
TARGET=appname

# compiler binary
CC=g++

# source directories
SRCDIR=./

# include directories
INCDIR=-I./

# gui resource
GUIRC=gui.fl

# build output directory
ODIR=build

# memory leak detection
# run binary with option:
#unset LD_PRELOAD
#MEMLEAK=-fsanitize=address

# compiler options
COPT=-O0 -Wall -pthread
CFLAGS=$(COPT) $(MEMLEAK) -I/usr/include/FL
LFLAGS=$(COPT) $(MEMLEAK) -lfltk -lfltk_forms

################### Non Configurable ########################

CSRC=$(wildcard $(SRCDIR)/*.cxx)
COBJ=$(patsubst $(SRCDIR)/%.cxx,$(ODIR)/%.o,$(CSRC))

all: uic dir $(ODIR)/$(TARGET)

dir:
	mkdir -p $(ODIR)

uic: $(GUIRC)
	fluid -c $(GUIRC)

$(ODIR)/$(TARGET): $(COBJ)
	$(CC) $(COBJ) $(LFLAGS) -o $(ODIR)/$(TARGET)

$(ODIR)/%.o: $(SRCDIR)/%.cxx
	$(CC) $(INCDIR) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(ODIR)/

.PHONY: all dir uic clean

