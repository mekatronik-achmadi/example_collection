# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 22:10:50 2016

@author: achmadi
"""

from ode4solve import ODE4solve

sv = ODE4solve()

konstanta = [0,1E-8,0,0,5E-7]
y_awal = [0,0,0,0]

t_input = sv.T(200.,0.01)

solusi = sv.solve(y_awal,t_input,konstanta)

sv.plot(t_input,solusi)