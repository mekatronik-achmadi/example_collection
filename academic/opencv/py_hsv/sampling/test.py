#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
from pixcount import PixelCount

imagePath = sys.argv[1]
pixc = PixelCount()

pixc.set_lower(65,190,90) 
pixc.set_upper(85,220,130)

pixtotal = pixc.pxl_img(imagePath)
print(pixtotal)

pixc.wait()
