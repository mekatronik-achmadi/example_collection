#! /usr/bin/python2
# -*- coding: utf-8 -*-

import os
import platform

import pygtk
pygtk.require('2.0')
    
import gtk
import gtk.glade

class InfoTest:
    def __init__(self):
        guibuilder=gtk.Builder()
        guibuilder.add_from_file("./info.glade")
        guibuilder.connect_signals(self)
        
        window=guibuilder.get_object("frmInfo")
        window.connect("destroy",self.on_destroy)
        
        self.btnConsole=guibuilder.get_object("btnConsole")
        self.btnDialog=guibuilder.get_object("btnDialog")
        
        self.btnConsole.connect("clicked",self.btnConsole_clicked)
        self.btnDialog.connect("clicked",self.btnDialog_clicked)
        
        window.show()
        
    def on_destroy(self, widget):
        gtk.main_quit()
        
    def Info(self, message = "empty message"):
        md = gtk.MessageDialog(None, gtk.DIALOG_DESTROY_WITH_PARENT, gtk.MESSAGE_INFO, gtk.BUTTONS_OK, message)
        md.run()
        md.destroy()
    
    def  InfoMessage( self):
        msginfo = "System Information\n\n"
        msginfo += "Python version: %s\n" % platform.python_version()
        msginfo += "Gtk version: %i.%i.%i\n\n" %  (gtk.gtk_version[0], gtk.gtk_version[1], gtk.gtk_version[2])
        msginfo += "PyGtk version: %i.%i.%i\n\n" %  (gtk.pygtk_version[0], gtk.pygtk_version[1], gtk.pygtk_version[2])
        
        msginfo += "OS Name: %s (%s)\n" % (platform.system(), os.name)
        if platform.system() == "Linux":
            msginfo += "Shell system: %s\n\n" % os.environ['SHELL']
        
        msginfo += "Machine: %s\n" %  platform.machine()
        msginfo += "Python Imp: %s\n" %  platform.python_implementation()
        
        return msginfo
        
    def btnDialog_clicked(self,widget):
        self.Info(self.InfoMessage())
        
    def btnConsole_clicked(self,widget):
        print "======================="
        print self.InfoMessage()
        print "======================="
        

app = InfoTest()
gtk.main()
