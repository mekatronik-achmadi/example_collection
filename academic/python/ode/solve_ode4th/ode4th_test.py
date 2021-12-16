# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 04:17:04 2016

@author: achmadi
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

def u(t):
    return (np.sign(t) + 1)

def fdy(y, t, params):
    x,x1,x2,x3 = y
    c1,c2,c3,c4,c5 = params
    
    dydt = [x1, x2, x3, -c1*x3 - c2*x2 - c3*x1 - c4*x + c5*u(t)]
    return dydt
    
c1 = 0
c2 = 1E-8
c3 = 0
c4 = 0
c5 = 5E-7

x_0 = 0
x1_0 = 0
x2_0 = 0
x3_0 = 0

params = [c1,c2,c3,c4,c5]
y0 = [x_0, x1_0, x2_0, x3_0]

tStop = 200.
tInc = 0.05
t = np.arange(0., tStop, tInc)

psoln = odeint(fdy, y0, t, args=(params,))

plt.plot(t, psoln[:, 0], 'b', label='x')
plt.plot(t, psoln[:, 1], 'g', label='x1')
plt.plot(t, psoln[:, 2], 'r', label='x2')
plt.plot(t, psoln[:, 3], 'k', label='x3')
plt.legend(loc='best')
plt.xlabel('t')
plt.grid()
plt.show()