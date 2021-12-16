#!/usr/bin/python3
# -*- coding: utf-8 -*-

import threading
import time

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import GLib, Gtk, GObject


class GtkThds(Gtk.Window):
    """docstring for GtkThds"""
    def __init__(self):
        super(GtkThds, self).__init__()
        self.mainUI()

    def mainUI(self):
        self.set_title("Gtk Thds")
        self.set_default_size(200, 100)
        self.connect("destroy", Gtk.main_quit)

        self.prgs = Gtk.ProgressBar(show_text=True)
        self.add(self.prgs)

        thd = threading.Thread(target=self.test_target)
        thd.daemon = True
        thd.start()

    def update_progress(self,i):
        self.prgs.set_fraction((i+1)/50)
        self.prgs.set_text(str(i))
        return False

    def test_target(self):
        for i in range(50):
            GLib.idle_add(self.update_progress,i)
            time.sleep(0.2)

if __name__ == "__main__":
    gtkthd = GtkThds()
    gtkthd.show_all()
    Gtk.main()
