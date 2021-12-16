#!/usr/bin/python

import sys
try:
 	import pygtk
  	pygtk.require('2.0')
except:
  	pass
try:
	import gtk
  	import gtk.glade
except:
	sys.exit(1)

class HelloGTK:
	def __init__(self):
		guibuilder=gtk.Builder()
		guibuilder.add_from_file("hello.glade")
		guibuilder.connect_signals(self)
		window=guibuilder.get_object("window1")
		window.set_default_size(200,200)
		window.connect("destroy",self.on_destroy)
		window.show()
	def on_destroy(self,widget):
		gtk.main_quit()
		
if __name__ == "__main__":
	app = HelloGTK()
	gtk.main()
