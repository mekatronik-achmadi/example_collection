#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sat May 12 22:08:52 2018

@author: fotoniks
"""

import cv2
import numpy as np


def nothing(x):
    pass

cap = cv2.VideoCapture(0)
cv2.namedWindow('image')
matrix = np.zeros((480,640,3),'uint8')
posisi =[]
maks = 0


switch = '0 : OFF \n1 : ON'
cv2.createTrackbar(switch, 'image',0,1,nothing)

ret, frame = cap.read()

while(True):
    cv2.imshow('image',frame)


#    window = np.ones((510,1320,3))*255

    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    lower_blue = np.array([15,50,10])
    upper_blue = np.array([25,255,255])

    mask = cv2.inRange(hsv, lower_blue, upper_blue)



    num_kernel = 20
    kernel = np.zeros((num_kernel,num_kernel),np.uint8)
    kernel[:,num_kernel//2] = 1
    kernel[num_kernel//2,:] = 1

    opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
#    kernel[:,num_kernel//2] = 0
#    kernel[num_kernel//2,:] = 1
    opening = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, kernel)

    image,contour,_ = cv2.findContours(opening,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

    maks = 0

    for c in contour:
            area = cv2.contourArea(c)
            if area > maks:
                x,y,w,h = cv2.boundingRect(c)
                x = x+w//2
                y = y+w//2
                maks = area



    cv2.rectangle(frame,(x-(w//2),y-(h//2)),(x+w//2,y+h//2),(255,255,255),2)
    s = cv2.getTrackbarPos(switch,'image')
    if s == 1:
        cv2.circle(matrix,(x,y), 2, (1,1,1), -1)
        posisi.append([x,y])
        if len(posisi) > 1:
            cv2.line(matrix,(posisi[len(posisi)-2][0],posisi[len(posisi)-2][1]),(x,y),(1,1,1),4)

    inv = matrix < 1

    frame = (frame * inv) +(matrix*255)



    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
