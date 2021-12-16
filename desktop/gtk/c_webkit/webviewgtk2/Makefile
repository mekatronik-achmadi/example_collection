INSTALL = installs
BUILD= gcc -v -v -Wall
LIBS= `pkg-config --cflags --libs gtk+-2.0 --libs webkit-1.0`
APP=achmadi-browser

build: main.c
	$(BUILD) -o $(APP) main.c $(LIBS)

install:
	$(INSTALL) -d $(DESTDIR)/usr/bin/
	$(INSTALL) -m 755 $(APP) $(DESTDIR)/usr/bin/
	$(INSTALL) -d $(DESTDIR)/usr/share/applications/
	$(INSTALL) -m 755 $(APP).desktop $(DESTDIR)/usr/share/applications/

.PHONY: build install

