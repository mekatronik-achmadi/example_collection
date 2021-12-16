# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 05:40:44 2016

@author: achmadi
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint
#odeint?    # Uncomment to view the help file for this function

# Define a function which calculates the derivative
def dy_dx(y, x):
    return x - y

xs = np.linspace(0,5,100)
y0 = 1.0
ys = odeint(dy_dx, y0, xs)
ys = np.array(ys).flatten()

plt.plot(xs, ys)
plt.xlabel("x")
plt.ylabel("y");