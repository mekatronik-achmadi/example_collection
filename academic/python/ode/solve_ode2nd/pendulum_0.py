# -*- coding: utf-8 -*-
"""
Created on Sun Dec 18 21:00:04 2016

@author: achmadi
"""
import matplotlib.pyplot as plt
from scipy.integrate import odeint
import numpy as np

# theta''(t) + b*theta'(t) + c*sin(theta(t)) = 0
# theta'(t) = omega(t)
# omega'(t) = -b*omega(t) - c*sin(theta(t))

def pend(y, t, b, c):
    theta, omega = y
    dydt = [omega, -b*omega - c*np.sin(theta)]
    return dydt
    
b = 0.25
c = 5.0
y0 = [np.pi - 0.1, 0.0]
t = np.linspace(0, 10, 101)
sol = odeint(pend, y0, t, args=(b, c))

plt.plot(t, sol[:, 0], 'b', label='theta(t)')
plt.plot(t, sol[:, 1], 'g', label='omega(t)')
plt.legend(loc='best')
plt.xlabel('t')
plt.grid()
plt.show()