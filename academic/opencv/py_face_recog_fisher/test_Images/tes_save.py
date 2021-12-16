#!/usr/bin/python

from FRecog import FaceRec
from datetime import datetime
from os import path

list_nama = ["mas_Brewok", "mas_Mulus"]
haar = "haarcascade_frontalface_alt.xml"
filenm = "lbph_train_" + datetime.now().strftime("%d%m%y_%H%M") + ".yml"

fc = FaceRec("lbph",list_nama,haar)

aface, alabel = fc.prepare_train('mydata/training')
fc.training(aface,alabel)

if path.exists(filenm):
    print("file %s sudah ada" % filenm)
else:
    fc.save_train(filenm)
    print("training disimpan di %s" % filenm)
