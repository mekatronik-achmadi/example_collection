#!/usr/bin/python

from FRecog import FaceRec
from os import path
import sys

list_nama = ["mas_Brewok", "mas_Mulus"]
haar = "haarcascade_frontalface_alt.xml"
filenm = "lbph_train_310319_1045"  + ".yml"

fc = FaceRec("lbph",list_nama,haar)

if path.exists(filenm):
    fc.load_train(filenm)
    print("file %s sudah di load" % filenm)
else:
    print("file %s tidak ada" % filenm)
    sys.exit()

nama_img1, r1 = fc.guessing("mydata/test/brewok.jpg")
nama_img2, r2 = fc.guessing("mydata/test/mulus.jpg")

res_img1 = fc.draw_marker("mydata/test/brewok.jpg",r1,nama_img1)
res_img2 = fc.draw_marker("mydata/test/mulus.jpg",r2,nama_img2)

print("foto pertama adalah %s" % nama_img1)
print("foto kedua adalah %s" % nama_img2)
