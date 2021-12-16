# -*- coding: utf-8 -*-

import cv2
import numpy as np

class PixelCount:
    def __init__(self):
        self.upper_color = np.array([10,10,10])
        self.lower_color = np.array([0,0,0])
        
    def set_upper(self, hue, sat, val):
        self.upper_color = np.array([hue,sat,val])
        
    def set_lower(self, hue, sat, val):
        self.lower_color = np.array([hue,sat,val])
        
    def pxl_img(self, imgpath):
        img_ori = cv2.imread(imgpath)
        img_hsv = cv2.cvtColor(img_ori, cv2.COLOR_BGR2HSV)
        img_msk = cv2.inRange(img_hsv, self.lower_color, self.upper_color)
        img_and = cv2.bitwise_and(img_ori,img_ori, mask= img_msk)
        
        pxlcnt = cv2.countNonZero(img_msk)
        self.show_img(img_and)
        return pxlcnt
    
    def show_img(self, imgtoshow, wid=1366, hei=768):
        cv2.namedWindow('image',cv2.WINDOW_NORMAL)
        cv2.imshow("image", imgtoshow)
        cv2.resizeWindow('image', wid,hei)
        
    def wait(self):
        cv2.waitKey(0)
        
        
