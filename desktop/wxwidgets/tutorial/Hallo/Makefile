APP = Hallo
SRC = hallo.cpp

CC     = g++
WXGTK3 = wx-config-gtk3 --cxxflags --libs
CGTK3  = pkg-config gtk+-3.0 --cflags

all:
	$(CC) -o $(APP) $(SRC) -I. `$(WXGTK3)` `$(CGTK3)`

clean:
	rm -f $(APP) *.plist
