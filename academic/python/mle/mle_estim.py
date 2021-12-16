# -*- coding: utf-8 -*-
"""
Created on Sun Jan  1 10:13:43 2017

@author: achmadi
"""

import matplotlib.pyplot as plt
import numpy as np
import mle

# Define model
x = mle.var('x', observed=True, vector=True)
y = mle.var('y', observed=True, vector=True)

a = mle.var('a')
b = mle.var('b')
sigma = mle.var('sigma')

model = mle.Normal(y, a * x + b, sigma)

# Generate data
xs = np.linspace(0, 2, 20)
#ys = 0.5 * xs + 0.3
ys = 0.5 * xs + 0.3 + np.random.normal(0, 0.05, 20)

# Fit model to data
result = model.fit({'x': xs, 'y': ys}, {'a': 1, 'b': 1, 'sigma': 1})
print(result)

coef = result['x']
y0 = coef['a']*xs + coef['b']
plt.plot(xs,ys, 'r', label='measured')
plt.plot(xs,y0, 'b', label='estimated')
plt.legend(loc='best')
plt.grid()
plt.show()
