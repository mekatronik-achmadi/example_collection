# -*- coding: utf-8 -*-
"""
Created on Wed Feb 22 22:40:42 2017

@author: achmadi
"""

import numpy as np
from scipy import signal as sg
from scipy.signal import butter, lfilter
import matplotlib.pyplot as plt

def butter_bandpass(lcut,hcut,freqsam,order=5):
    nyquist = freqsam/2
    low = lcut/nyquist
    high = hcut/nyquist
    b,a =  butter(order, [low, high], btype='band')
    return b,a
    
def bandpass_filter(input,lcut,hcut,freqsam,order=5):
    b,a = butter_bandpass(lcut, hcut, freqsam, order=order)
    result = lfilter(b, a, input)
    return result
    
def freqbound(f_center,f_width):
    low = f_center - (f_width/2)
    high = f_center + (f_width/2)
    return low,high
    
if __name__ == "__main__":
    
    fs = 2000
    N = 1024
    noise_power = 2
    
    lowcut,highcut = freqbound(500,200)

    t = np.arange(N)/fs
    ys = np.sin((1000*np.pi*t)+(np.pi/6))

    yn = np.random.normal(scale = 1,size=t.shape)
    
    y = ys + yn
    
    yf = bandpass_filter(y,lowcut,highcut,fs,order=6)    

    plt.figure(1)
    plt.subplot(3,1,1)
    plt.plot(t,ys,'k')
    plt.ylim([-5, 5])
    plt.ylabel('Original')
    plt.subplot(3,1,2)
    plt.plot(t,y,'k')
    plt.ylim([-5, 5])
    plt.ylabel('Buried')
    plt.subplot(3,1,3)
    plt.plot(t,yf,'k')
    plt.ylim([-5, 5])
    plt.ylabel('Filtered')
    plt.xlabel('t')
    plt.show()
    
    fori, Pori = sg.periodogram(ys, fs, 'flattop', scaling='spectrum')
    fbur, Pbur = sg.periodogram(y, fs, 'flattop', scaling='spectrum')
    ffil, Pfil = sg.periodogram(yf, fs, 'flattop', scaling='spectrum')

    plt.figure(2)
    plt.subplot(3,1,1)
    plt.semilogy(fori, np.sqrt(Pori),'k')
    plt.xlim([0, 1000])
    plt.ylim([1e-2, 1e1])
    plt.ylabel('Original')
    plt.subplot(3,1,2)
    plt.semilogy(fbur, np.sqrt(Pbur),'k')
    plt.xlim([0, 1000])
    plt.ylim([1e-2, 1e1])
    plt.ylabel('Burried')
    plt.subplot(3,1,3)
    plt.semilogy(ffil, np.sqrt(Pfil),'k')
    plt.xlim([0, 1000])
    plt.ylim([1e-2, 1e1])
    plt.ylabel('Filtered')
    plt.xlabel('frequency [Hz]')
    plt.show()
