#!/usr/bin/python

from FRecogCam import FaceRecCam
import RPi.GPIO as GPIO
from os import path
import sys
import cv2

list_nama = ["fafang", "dhiaz", "wildan"]
haar = "haarcascade_frontalface_alt.xml"
filenm = "fisher_train_220419_1306"  + ".yml"

fc = FaceRecCam("fisher",list_nama,haar)

if path.exists(filenm):
    fc.load_train(filenm)
    print("file %s sudah di load" % filenm)
else:
    print("file %s tidak ada" % filenm)
    sys.exit()

vid = cv2.VideoCapture(0)

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)


while True:
    ret, imgv = vid.read()
    img = fc.imresize(imgv)
    nama_img, rec, confi = fc.guessing_cam(img)

    if nama_img is not None:
        label = "%s (%i)" % (nama_img,confi)
        res_img = fc.draw_marker_cam(img,rec,label)
        cv2.imshow('Deteksi', res_img)
        
        if nama_img == "fafang":
            GPIO.output(4, GPIO.LOW) # active-low
        else:
            GPIO.output(4, GPIO.HIGH) # active-low
            
    else:
        cv2.imshow('Deteksi', img)
        GPIO.output(4, GPIO.HIGH) # active-low 

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

GPIO.cleanup()
vid.release()
cv2.destroyAllWindows()
