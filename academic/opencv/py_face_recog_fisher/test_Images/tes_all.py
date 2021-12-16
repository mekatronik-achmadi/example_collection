#!/usr/bin/python

from FRecog import FaceRec

list_nama = ["mas_Brewok", "mas_Mulus"]
haar = "haarcascade_frontalface_alt.xml"

fc = FaceRec("lbph",list_nama,haar)

aface, alabel = fc.prepare_train('mydata/training')
fc.training(aface,alabel)

nama_img1, r1 = fc.guessing("mydata/test/brewok.jpg")
nama_img2, r2 = fc.guessing("mydata/test/mulus.jpg")

res_img1 = fc.draw_marker("mydata/test/brewok.jpg",r1,nama_img1)
res_img2 = fc.draw_marker("mydata/test/mulus.jpg",r2,nama_img2)

print("foto pertama adalah %s" % nama_img1)
print("foto kedua adalah %s" % nama_img2)
