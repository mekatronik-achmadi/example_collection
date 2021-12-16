#!/usr/bin/python2
# -*- coding: utf-8 -*-

import os
import platform

import wx
import info_gui

class InfoTest(info_gui.frmInfo):
    def __init__(self,parent):
        info_gui.frmInfo.__init__(self,parent)

    def Info(parent, message = "empty message", caption = 'untitled'):
        dlg = wx.MessageDialog(parent, message, caption, wx.OK | wx.ICON_INFORMATION)
        dlg.ShowModal()
        dlg.Destroy()

    def  InfoMessage( self):
        msginfo = "System Information\n\n"
        msginfo += "Python version: %s\n" % platform.python_version()
        msginfo += "wxWidget version: %s\n\n" %  wx.version()

        msginfo += "OS Name: %s (%s)\n" % (platform.system(), os.name)
        if platform.system() == "Linux":
            msginfo += "Shell system: %s\n\n" % os.environ['SHELL']

        msginfo += "Machine: %s\n" %  platform.machine()
        msginfo += "Python Imp: %s\n" %  platform.python_implementation()

        return msginfo

    def infoDialog(self, event):
        self.Info(self.InfoMessage(),"System Information")

    def infoConsole( self, event ):
        print "======================="
        print self.InfoMessage()
        print "======================="

app = wx.App(False)
frame = InfoTest(None)
frame.Show(True)
app.MainLoop()
