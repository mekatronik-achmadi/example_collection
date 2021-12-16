#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

tes00=np.genfromtxt('tes00-trace.dat')
tes10=np.genfromtxt('tes10-trace.dat')
tes01=np.genfromtxt('tes01-trace.dat')
tes11=np.genfromtxt('tes11-trace.dat')

tes_x = tes00[:,0]*1000

tes00y = tes00[:,1]
tes10y = tes10[:,1]
tes01y = tes01[:,1]
tes11y = tes11[:,1]

plt.figure(0)
plt.xlabel('distance (s)')
plt.ylabel('power (dB)')
plt.title('Trace Result')
plt.plot(
        tes_x,tes00y,'k',
        tes_x,tes10y,'r',
        tes_x,tes01y,'g',
        tes_x,tes11y,'b',)
plt.show()
