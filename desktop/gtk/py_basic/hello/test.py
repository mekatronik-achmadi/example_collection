#!/usr/bin/python

import sys
import os
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
		guibuilder.add_from_file("test.glade")
		guibuilder.connect_signals(self)
		window=guibuilder.get_object("window1")
		window.connect("destroy",self.on_destroy)
		window.set_default_size(200,200)
		window.set_position(gtk.WIN_POS_CENTER)
		button=guibuilder.get_object("btnTest")
		button.connect("clicked",self.on_test)
		window.show()
	def on_destroy(self,widget):
		gtk.main_quit()
	def on_test(self,widget):
		print "hello"
		os.system("echo \"world\n\"");
		msgbox=gtk.MessageDialog(None,gtk.DIALOG_DESTROY_WITH_PARENT, gtk.MESSAGE_INFO, gtk.BUTTONS_CLOSE, "HelloWorld")
		msgbox.run()
		msgbox.destroy()
		
if __name__ == "__main__":
	app = HelloGTK()
	gtk.main()
