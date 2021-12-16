#!/usr/bin/python
# coding: utf-8


import cv2.cv as cv
import cv2 as cv2
import time
import numpy as np
import RPi.GPIO as GPIO


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)


#HSV warna merah lilin
Hmin = 0
Hmax = 6
Smin = 0
Smax = 3
Vmin = 140
Vmax = 255


 # integer range HSV
rangeMin = np.array([Hmin, Smin, Vmin], np.uint8)
rangeMax = np.array([Hmax, Smax, Vmax], np.uint8)

# masukkan minimum area biner
minArea = 450


# nama output gambar

cv.NamedWindow("Entrada")
cv.NamedWindow("HSV")
cv.NamedWindow("Thre")
cv.NamedWindow("Erosao")


capture = cv2.VideoCapture(0)

# image resolusi kamera
width = 320
height = 240


if capture.isOpened():
  capture.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, width)
  capture.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, height)
  GPIO.output(17, GPIO.HIGH)
  GPIO.output(27, GPIO.LOW)

  
while True:
    ret, entrada = capture.read()
    imgHSV = cv2.cvtColor(entrada,cv2.cv.CV_BGR2HSV)	
    imgThresh = cv2.inRange(imgHSV, rangeMin, rangeMax)
    imgErode = cv2.erode(imgThresh, None, iterations = 3)
    moments = cv2.moments(imgErode, True)
    
# masukkan titik berat tengah area    
    
    if moments['m00'] >= minArea:
		
       x1 = moments['m10'] / moments['m00']
       y1 = moments['m01'] / moments['m00']
       print(x1, ", ", y1)
       cv2.circle(entrada, (int(x1), int(y1)), 5, (0, 255, 0), -1)
    
    cv2.imshow("Entrada",entrada)
    cv2.imshow("HSV", imgHSV)
    cv2.imshow("Thre", imgThresh)
    cv2.imshow("Erosao", imgErode)
    GPIO.output(17, GPIO.LOW)
    GPIO.output(27, GPIO.HIGH)
    
		
    
    if moments['m00'] < minArea:
       GPIO.output(17, GPIO.HIGH)
       GPIO.output(27, GPIO.LOW)

    
	
	
    if cv.WaitKey(10) == 27:
        break
cv.DestroyAllWindows()
