#!/usr/bin/python
# -*- coding: utf-8 -*-

from fltk import Fl,Fl_Window,Fl_Button,fl_message
import sys

class Template():
    def __init__(self):
        wind = Fl_Window(100,100,200,100)
        wind.label('FLTK Python')
        btnMsg = Fl_Button(0,30,200,30,'Message')
        btnQuit = Fl_Button(0,70,200,30,'Quit')

        btnMsg.callback(self.Msg)
        btnQuit.callback(self.Quit)

        wind.end()
        wind.show()

        Fl.scheme('gtk+')
        Fl.run()

    def Msg(self,widget):
        fl_message("FLTK Python Template")

    def Quit(self,widget):
        sys.exit()

if __name__ == "__main__":
    app = Template()
