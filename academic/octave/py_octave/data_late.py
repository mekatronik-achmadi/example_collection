# -*- coding: utf-8 -*-
"""
Created on Sun Jan  1 17:05:12 2017

@author: achmadi
"""

import numpy as np

class DataLate:
    def __init__(self):
        pass
    
    def late(self,data_input,late_order):
        ndim = np.shape(data_input)[0]
        mat_late = np.zeros(ndim)
        
        for i in range(late_order,ndim):
            mat_late[i] = data_input[i-late_order]
            
        return mat_late
        
