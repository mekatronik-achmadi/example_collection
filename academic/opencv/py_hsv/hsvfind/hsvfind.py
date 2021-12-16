#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import cv2
from hsvfind_ui import *
from PyQt4.QtCore import *
from PyQt4.QtGui import *

class HSV_Find(QMainWindow):
    def __init__ (self, parent=None):
        QWidget.__init__(self, parent)
        self.ui = Ui_HSVFind()
        self.ui.setupUi(self)
        
        self.tmr_hsv = QTimer()
        
        QObject.connect(self.ui.btnOpen, SIGNAL("clicked()"), self.image_open)
        QObject.connect(self.tmr_hsv, SIGNAL("timeout()"), self.view_hsv)
        
    def view_hsv(self):
        x_pos = self.ui.sldX.value()
        y_pos = self.ui.sldY.value()
        img_circ = self.img_input.copy()
        cv2.circle(img_circ,(x_pos,y_pos), 5, (255,0,0), 5)
        
        hue  = self.img_hsv[y_pos, x_pos, 0]
        sat  = self.img_hsv[y_pos, x_pos, 1]
        val  = self.img_hsv[y_pos, x_pos, 2]
        
        self.ui.txtH.setText(str(hue))
        self.ui.txtS.setText(str(sat))
        self.ui.txtV.setText(str(val))
        self.show_img(img_circ)
        
    def image_open(self):
        fileName=QFileDialog.getOpenFileName(self,"Buka Gambar", "Image files (*.jpg *.gif)")
        if fileName:
            self.img_input = cv2.imread(fileName)
            self.img_shape = self.img_input.shape
            self.img_row = self.img_shape[0]
            self.img_col = self.img_shape[1]
            self.img_hsv = cv2.cvtColor(self.img_input, cv2.COLOR_BGR2HSV) 
            
            self.ui.sldX.setMaximum(self.img_col)
            self.ui.sldY.setMaximum(self.img_row)

            self.tmr_hsv.start(100)
            
#            print("%s %s" % (self.img_col, self.img_row))
#            self.show_img( self.img_input)
             
            
    def show_img(self, imgtoshow, wid=1280, hei=720):
        cv2.namedWindow('image',cv2.WINDOW_NORMAL)
        cv2.imshow("image", imgtoshow)
        cv2.resizeWindow('image', wid,hei)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    my_main_app = HSV_Find()
    my_main_app.show()
    sys.exit(app.exec_())
