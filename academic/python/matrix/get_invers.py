# -*- coding: utf-8 -*-
"""
Created on Sun Dec 18 21:51:08 2016

@author: achmadi
"""

import numpy as np
import sympy as sy

A= np.matrix([
    [0,1,0,0],
    [0,0,1,0],
    [0,0,0,1],
    [0,0,-1E-8,0] ])
    
B = np.matrix([
    [0],
    [0],
    [0],
    [5E-7] ])
    
C = np.matrix([[1,0,0,0]])

I = np.identity(4)

l = sy.symbols('l',real=True)

eig = l*I - A
s_inv = sy.Matrix(eig)

m_inv = s_inv.inv()

print(m_inv)