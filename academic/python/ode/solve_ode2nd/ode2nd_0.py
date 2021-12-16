# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 05:59:36 2016

@author: achmadi
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

def dU_dx(U, x):
    # Here U is a vector such that y=U[0] and z=U[1]. This function should return [y', z']
    return [U[1], -2*U[1] - 2*U[0] + np.cos(2*x)]
U0 = [0, 0]
xs = np.linspace(0, 10, 500)
Us = odeint(dU_dx, U0, xs)
ys = Us[:,0]


plt.plot(xs,ys)
plt.xlabel("x")
plt.ylabel("y")
plt.title("Damped harmonic oscillator");