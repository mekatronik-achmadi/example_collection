#!/usr/bin/python

import gtk
window=gtk.Window(gtk.WINDOW_TOPLEVEL)
window.set_default_size(200,200)
window.set_position(gtk.WIN_POS_CENTER)
window.set_title("test")
window.connect("destroy",gtk.main_quit)
window.show()
gtk.main()
