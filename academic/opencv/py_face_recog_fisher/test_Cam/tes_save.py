#!/usr/bin/python

from FRecogCam import FaceRecCam
from datetime import datetime
from os import path

list_nama = ["fafang", "dhiaz", "wildan"]
haar = "haarcascade_frontalface_alt.xml"
filenm = "fisher_train_" + datetime.now().strftime("%d%m%y_%H%M") + ".yml"

fc = FaceRecCam("fisher",list_nama,haar)

aface, alabel = fc.prepare_train('mydata/training')
fc.training(aface,alabel)

if path.exists(filenm):
    print("file %s sudah ada" % filenm)
else:
    fc.save_train(filenm)
    print("training disimpan di %s" % filenm)
