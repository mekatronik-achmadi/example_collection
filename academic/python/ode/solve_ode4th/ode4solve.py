# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 21:49:53 2016

@author: achmadi
"""

import numpy as np
import scipy.integrate as sy
import matplotlib.pyplot as plt

class ODE4solve:
    def __init__(self):
        pass
    
    def T(self, t_stop, t_inc):
        return np.arange(0., t_stop, t_inc)
    
    def u(self, t):
        return (np.sign(t) + 1)
        
    def fdydt(self, y, t, params):
        x,x1,x2,x3 = y
        c1,c2,c3,c4,c5 = params
        
        dydt = [x1, x2, x3, -c1*x3 - c2*x2 - c3*x1 - c4*x + c5*self.u(t)]
        return dydt
    
    def solve(self, y0, t, params):
        return sy.odeint(self.fdydt, y0, t, args=(params,))
        
    def plot(self, t, psoln):
        plt.plot(t, psoln[:, 0], 'b', label='x')
        plt.plot(t, psoln[:, 1], 'g', label='x1')
        plt.plot(t, psoln[:, 2], 'r', label='x2')
        plt.plot(t, psoln[:, 3], 'k', label='x3')
        plt.legend(loc='best')
        plt.xlabel('t')
        plt.grid()
        plt.show()    