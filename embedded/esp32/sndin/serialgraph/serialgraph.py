#!/usr/bin/python
# -*- coding: utf-8 -*-

import tkinter as tk
from tkinter import font

from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg,NavigationToolbar2Tk)
import matplotlib.animation as anim
from matplotlib.figure import Figure
from matplotlib import style

import os
import sys
import numpy as np
import serial as ser
from time import sleep
from threading import Thread

class SerialGraph():

    dataLong = 1024
    baudRate = 115200
    plotUpd = True
    dataUpd = True
    dataIdX = 0

    def __init__(self):
        super(SerialGraph, self).__init__()

        self.gui = tk.Tk()
        self.gui.geometry("600x400")
        self.gui.resizable(False,False)
        self.gui.title("Serial Graph")

        graphfrm = tk.Frame(self.gui)

        self.X = np.arange(0,self.dataLong,1)
        self.Y = np.zeros(self.dataLong,dtype='i2')

        self.timeData = np.asarray([self.X])
        self.ampData = np.asarray([self.Y])

        fig = Figure(figsize=(11,9),dpi=100,facecolor='white',tight_layout=True)

        ax1 = fig.add_subplot(111)
        ax1.set_facecolor('white')
        ax1.grid(True,which='both',ls='-')
        ax1.set_title('Serial Data Plot')
        ax1.set_xlabel('Data Points')
        ax1.set_ylabel('Serial Value')
        self.line1, = ax1.plot(self.X, self.Y)
        ax1.relim()
        ax1.autoscale_view()

        style.use('ggplot')
        canvas = FigureCanvasTkAgg(fig, master=graphfrm)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.LEFT)

        graphfrm.pack(side=tk.TOP,expand=True)

        self.serPort = ser.Serial(port=sys.argv[1],baudrate=self.baudRate,timeout=0)

        aniplot = anim.FuncAnimation(
                fig,
                self.graphUpdate,
                interval=0.00005,
                repeat=False,
                cache_frame_data=False)
        aniplot._start()

        self.serThd = Thread(target=self.serialRead).start()

        self.gui.protocol('WM_DELETE_WINDOW',self.guiClosing)
        self.gui.mainloop()

    def guiClosing(self):
        self.dataUpd = False

        if self.serPort.is_open:
            self.serPort.close()

        self.gui.destroy()

    def arrayValue(self,val_Y):
        self.Y[self.dataIdX] = val_Y

        self.dataIdX = self.dataIdX + 1

        if self.dataIdX == self.dataLong-1:
            self.dataIdX = 0

    def portRead(self):
        try:
            dataIn = self.serPort.readline()
        except ser.SerialException as e:
            print(e)
            return None
        except TypeError as e:
            print(e)
            self.serPort.close()
            return None
        else:
            return dataIn

    def serialRead(self):
        while self.dataUpd:
            if self.serPort.is_open:
                serVal = self.portRead()
                try:
                    valY = int(serVal)
                    self.arrayValue(valY)
                except ValueError:
                    pass

            if os.name == 'posix':
                sleep(0.0001)

    def graphUpdate(self, args):
        if self.plotUpd:
            self.line1.set_data(self.X,self.Y)

if __name__ == "__main__":
    sergraph = SerialGraph()
