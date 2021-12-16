#!/usr/bin/python

import RPi.GPIO as GPIO
import os
import sys
import cv2
import numpy as np

haar = "haarcascade_frontalface_alt.xml"

def imresize(imgin,rasio=50):
	imW = int(imgin.shape[1] * rasio/100)
	imH = int(imgin.shape[0] * rasio/100)
	imres = cv2.resize(imgin,(imW,imH),interpolation=cv2.INTER_CUBIC)
	return imres

vid = cv2.VideoCapture(0)

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)

while True:
	ret, imgv = vid.read()
	img = imresize(imgv)
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	f_cas = cv2.CascadeClassifier(haar)
	face = f_cas.detectMultiScale(gray,scaleFactor=1.2,minNeighbors=5,minSize=(30, 30))

	if(len(face)!=0):
		(x,y,w,h) = face[0]
		cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)
		GPIO.output(4, GPIO.LOW) # active-low
	else:
		GPIO.output(4, GPIO.HIGH) # active-low

	cv2.imshow('Deteksi', img)

	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

GPIO.cleanup()
vid.release()
cv2.destroyAllWindows()
