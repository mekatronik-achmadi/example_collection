#!/usr/bin/python3

import re
import cv2
import imutils
import numpy as np
import pytesseract

class OCR():
    """docstring for ClassName"""
    def __init__(self):
        pass

    def run(self,fname):
        """docstring for run"""

        img = cv2.imread(fname,cv2.IMREAD_COLOR)
        img = cv2.resize(img,(640,480))

        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        gray = cv2.bilateralFilter(gray, 11, 17, 17)

        edged = cv2.Canny(gray, 30, 200)
        cnts = cv2.findContours(edged.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        cnts = sorted(cnts, key = cv2.contourArea, reverse=True)[:10]
        screenCnt = None

        for c in cnts:
            peri = cv2.arcLength(c, True)
            approx = cv2.approxPolyDP(c, 0.018 * peri, True)

            if len(approx) == 4:
                screenCnt = approx
                break

        if screenCnt is None:
            detected = 0
            print("no countour detected")
        else:
            detected = 1

        if detected == 1:
            cv2.drawContours(img, [screenCnt], -1, (0,0,255),3)

        mask = np.zeros(gray.shape, np.uint8)
        new_img = cv2.drawContours(mask, [screenCnt],0,255,-1)
        new_img = cv2.bitwise_and(img, img, mask=mask)

        (x,y) = np.where(mask==255)
        (topx, topy) = (np.min(x), np.min(y))
        (botx, boty) = (np.max(x),np.max(y))
        img_crop = gray[topx:botx+1, topy:boty+1]

        platno = str(pytesseract.image_to_string(img_crop, config='--psm 11'))
        platno = re.sub(r'\W','',platno)
        print("detected number plate: ",platno)

        winname = 'Number: %s' % platno
        cv2.namedWindow(winname)
        cv2.moveWindow(winname,10,160)
        cv2.imshow(winname,img)

        cv2.waitKey(0)
        cv2.destroyAllWindows()

if __name__ == '__main__':
    pyocr = OCR()
    pyocr.run('coba2.jpg')
