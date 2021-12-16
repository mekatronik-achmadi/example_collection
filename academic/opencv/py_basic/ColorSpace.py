#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sat May 12 16:36:30 2018

@author: fotoniks
"""

import cv2
import numpy as np


cap = cv2.VideoCapture(0)
mat_1 = [[17.8824,43.5161,4.1193],[3.4557,27.1554,3.8671],[0.02996,0.18431,1.4670]]
mat_2 = [[0,2.02344,-2.52581],[0,1,0],[0,0,1]]
mat_3 = [[0.0809,-0.1305,0.1167],[-0.0102,0.054,-0.1136],[-0.0003,-0.0041,0.6935]]
#

mat = np.dot(mat_2,mat_1)
mat_tot = np.dot(mat_3,mat)


#mat_tot=[[0.95 , 0.05 , 0.0]  ,  [0.0  , 0.433, 0.567],  [0.0  , 0.475 ,0.525]]

while(True):

#    window = np.ones((510,1320,3))*255

    ret, ori = cap.read()


    x = ori.shape[0]
    y = ori.shape[1]

    asu = np.zeros((x,y,3))

    asu[:,:,2]=mat_tot[0][0]*ori[:,:,2]+mat_tot[0][1]*ori[:,:,1]+mat_tot[0][2]*ori[:,:,0]
    asu[:,:,1]=mat_tot[1][0]*ori[:,:,2]+mat_tot[1][1]*ori[:,:,1]+mat_tot[1][2]*ori[:,:,0]
    asu[:,:,0]=mat_tot[2][0]*ori[:,:,2]+mat_tot[2][1]*ori[:,:,1]+mat_tot[2][2]*ori[:,:,0]


    wasu = asu.astype(np.uint8)

#    window[20:500,10:650,:] = ori
#    window[20:500,660:1300,:] = wasu

    cv2.imshow('Persepsi manusia',ori)
    cv2.imshow('Persepsi anjing',wasu)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
