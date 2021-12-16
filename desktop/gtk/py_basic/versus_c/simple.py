#!/usr/bin/python

import gtk

guibuilder=gtk.Builder()
guibuilder.add_from_file("simple.glade")

window=guibuilder.get_object("window1")
window.set_default_size(200,200)
window.set_position(gtk.WIN_POS_CENTER)
window.set_title("simple")
window.connect("destroy",gtk.main_quit)

button=guibuilder.get_object("btnQuit")
button.connect("clicked",gtk.main_quit)

window.show()
gtk.main()
