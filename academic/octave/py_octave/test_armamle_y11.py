# -*- coding: utf-8 -*-
"""
Created on Sat Dec 31 07:46:11 2016

@author: achmadi
"""

#from scipy import stats as st
#import statsmodels.api as sm

import numpy as np
import matplotlib.pyplot as plt
import mle

from data_load import DataLoad
from data_late import DataLate

# used data is from 20 to 1450
# 20 to 700 for learning
# 700 to 1450 for validation

# =============================== LEARNING ===========================

# Load all data and plot
dat_all = DataLoad(20,1450)
dat_all.plot()

# load data for learning
dat_learn = DataLoad(20,700)

# load data for validation
dat_valid = DataLoad(700,1450)

#=========================================

# Define symbolic variabel
x1 = mle.var('x1', observed=True, vector=True)
x1_1 = mle.var('x1_1', observed=True, vector=True)
x1_2 = mle.var('x1_2', observed=True, vector=True)

x2 = mle.var('x2', observed=True, vector=True)
x2_1 = mle.var('x2_1', observed=True, vector=True)
x2_2 = mle.var('x2_2', observed=True, vector=True)

x3 = mle.var('x3', observed=True, vector=True)
x3_1 = mle.var('x3_1', observed=True, vector=True)
x3_2 = mle.var('x3_2', observed=True, vector=True)

y1 = mle.var('y1', observed=True, vector=True)
y1_1 = mle.var('y1_1', observed=True, vector=True)
y1_2 = mle.var('y1_2', observed=True, vector=True)

#=========================================

# Define symbolic coefision

a1 = mle.var('a1')
a1_1 = mle.var('a1_1')
a1_2 = mle.var('a1_2')

a2 = mle.var('a2')
a2_1 = mle.var('a2_1')
a2_2 = mle.var('a2_2')

a3 = mle.var('a3')
a3_1 = mle.var('a3_1')
a3_2 = mle.var('a3_2')

b1_1 = mle.var('b1_1')
b1_2 = mle.var('b1_2')

sigma = mle.var('sigma')

#=========================================

# Assigning variables
lt = DataLate()

vx1 = dat_learn.u11
vx1_1 = lt.late(vx1,1)
vx1_2 = lt.late(vx1,2)

vx2 = dat_learn.u12
vx2_1 = lt.late(vx2,1)
vx2_2 = lt.late(vx2,2)

vx3 = dat_learn.u13
vx3_1 = lt.late(vx3,1)
vx3_2 = lt.late(vx3,2)

vy1 = dat_learn.y11
vy1_1 = lt.late(vy1,1)
vy1_2 = lt.late(vy1,2)

#=========================================

# build model
model = mle.Normal(y1,
                   b1_1*y1_1 + b1_2*y1_2 +
                   a1*x1 + a1_1*x1_1 + a1_2*x1_2 +
                   a2*x2 + a2_1*x2_1 + a2_2*x2_2 +
                   a3*x3 + a3_1*x3_1 + a3_2*x3_2,
                   sigma)
                   
#=========================================

# solve model
# Metode: Maximum Likehood Estimation
estim = model.fit({
                    'y1':vy1, 'y1_1':vy1_1, 'y1_2':vy1_2,
                    'x1':vx1, 'x1_1':vx1_1, 'x1_2':vx1_2,
                    'x2':vx2, 'x2_1':vx2_1, 'x2_2':vx2_2,
                    'x3':vx3, 'x3_1':vx3_1, 'x3_2':vx3_2
                    },{
                    'b1_1':1,'b1_2':1,
                    'a1':1,'a1_1':1,'a1_2':1,
                    'a2':1,'a2_1':1,'a2_2':1,
                    'a3':1,'a3_1':1,'a3_2':1,
                    'sigma':1
                  })
print(estim)
estim_coef = estim['x']

# =============================== VALIDATION ===========================

# Assigning variables

wx1 = dat_valid.u11
wx1_1 = lt.late(wx1,1)
wx1_2 = lt.late(wx1,2)

wx2 = dat_valid.u12
wx2_1 = lt.late(wx2,1)
wx2_2 = lt.late(wx2,2)

wx3 = dat_valid.u13
wx3_1 = lt.late(wx3,1)
wx3_2 = lt.late(wx3,2)

measu_y = dat_valid.y11
#estim_y = np.zeros(dat_valid.dim)
estim_yy = np.zeros(dat_valid.dim)

#=========================================

# re-calculate model
# 2 step behind
# output excluded

#estim_y = + estim_coef['a1']*wx1 + estim_coef['a1_1']*wx1_1 + estim_coef['a1_2']*wx1_2 + estim_coef['a2']*wx2 + estim_coef['a2_1']*wx2_1 + estim_coef['a2_2']*wx2_2 + estim_coef['a3']*wx3 + estim_coef['a3_1']*wx3_1 + estim_coef['a3_2']*wx3_2

# re-calculate model
# 2 step behind
# output include

estim_yy[0] = estim_coef['b1_1']*estim_yy[0] + estim_coef['b1_2']*estim_yy[0] + estim_coef['a1']*wx1[0] + estim_coef['a1_1']*wx1_1[0] + estim_coef['a1_2']*wx1_2[0] + estim_coef['a2']*wx2[0] + estim_coef['a2_1']*wx2_1[0] + estim_coef['a2_2']*wx2_2[0] + estim_coef['a3']*wx3[0] + estim_coef['a3_1']*wx3_1[0] + estim_coef['a3_2']*wx3_2[0]
estim_yy[1] = estim_coef['b1_1']*estim_yy[0] + estim_coef['b1_2']*estim_yy[0] + estim_coef['a1']*wx1[1] + estim_coef['a1_1']*wx1_1[1] + estim_coef['a1_2']*wx1_2[1] + estim_coef['a2']*wx2[1] + estim_coef['a2_1']*wx2_1[1] + estim_coef['a2_2']*wx2_2[1] + estim_coef['a3']*wx3[1] + estim_coef['a3_1']*wx3_1[1] + estim_coef['a3_2']*wx3_2[1]
estim_yy[2] = estim_coef['b1_1']*estim_yy[1] + estim_coef['b1_2']*estim_yy[0] + estim_coef['a1']*wx1[2] + estim_coef['a1_1']*wx1_1[2] + estim_coef['a1_2']*wx1_2[2] + estim_coef['a2']*wx2[2] + estim_coef['a2_1']*wx2_1[2] + estim_coef['a2_2']*wx2_2[2] + estim_coef['a3']*wx3[2] + estim_coef['a3_1']*wx3_1[2] + estim_coef['a3_2']*wx3_2[2]

for i in range(3,dat_valid.dim):
    estim_yy[i] = estim_coef['b1_1']*estim_yy[i-1] + estim_coef['b1_2']*estim_yy[i-2] + estim_coef['a1']*wx1[i] + estim_coef['a1_1']*wx1_1[i] + estim_coef['a1_2']*wx1_2[i] + estim_coef['a2']*wx2[i] + estim_coef['a2_1']*wx2_1[i] + estim_coef['a2_2']*wx2_2[i] + estim_coef['a3']*wx3[i] + estim_coef['a3_1']*wx3_1[i] + estim_coef['a3_2']*wx3_2[i]

##=========================================

## plot result
plt.figure()
plt.title('Compare')
plt.plot(dat_valid.t,measu_y, 'r', label='measured')
#plt.plot(dat_valid.t,estim_y, 'g', label='estimation')
plt.plot(dat_valid.t,estim_yy, 'b', label='estimation-y')
plt.legend(loc='best')
plt.grid()
plt.show()