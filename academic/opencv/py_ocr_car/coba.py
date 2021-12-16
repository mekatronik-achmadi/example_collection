#!/usr/bin/python3

import os
import glob
import cv2
from ocr import OCR

pyocr = OCR()
os.chdir('./')
for fname in glob.glob("*.jpg"):
    pyocr.run(fname)
