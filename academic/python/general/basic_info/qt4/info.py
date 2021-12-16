#! /usr/bin/python2
# -*- coding: utf-8 -*-

import os
import sys
import platform
from PyQt4 import QtCore, QtGui
from info_ui import Ui_frmInfo

class InfoTest(QtGui.QMainWindow):
    def __init__ (self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_frmInfo()
        self.ui.setupUi(self)
        
        QtCore.QObject.connect(self.ui.btnDialog, QtCore.SIGNAL("clicked()"), self.btnDialog_clicked)
        QtCore.QObject.connect(self.ui.btnConsole, QtCore.SIGNAL("clicked()"), self.btnConsole_clicked)
        
    def Info(parent, message = "empty message", caption = 'untitled'):
        msg = QtGui.QMessageBox(QtGui.QMessageBox.Information,caption,message,QtGui.QMessageBox.Ok, parent)
        msg.show()
    
    def  InfoMessage( self):
        msginfo = "System Information\n\n"
        msginfo += "Python version: %s\n" % platform.python_version()
        msginfo += "Qt version: %s\n\n" %  QtCore.QT_VERSION_STR
        
        msginfo += "OS Name: %s (%s)\n" % (platform.system(), os.name)
        if platform.system() == "Linux":
            msginfo += "Shell system: %s\n\n" % os.environ['SHELL']
        
        msginfo += "Machine: %s\n" %  platform.machine()
        msginfo += "Python Imp: %s\n" %  platform.python_implementation()
        
        return msginfo
        
    def btnDialog_clicked(self):
        self.Info(self.InfoMessage(),"System Information")
        
    def btnConsole_clicked(self):
        print "======================="
        print self.InfoMessage()
        print "======================="
        
app = QtGui.QApplication(sys.argv)
my_main_app =  InfoTest()
my_main_app.show()
sys.exit(app.exec_())
