#!/usr/bin/python

from FRecogCam import FaceRecCam
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

nama_img, rec, confi = fc.guessing("mydata/test/1.jpg")

label = "%s (%i)" % (nama_img,confi)
res_img = fc.draw_marker("mydata/test/1.jpg",rec,label)

print("foto adalah %s & confi %i" % (nama_img,confi))
cv2.imshow(label,res_img)
