# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import cv2
import numpy as np
import time 

def nothing(x):
    pass


cap = cv2.VideoCapture(0)

cv2.namedWindow('Matrix')
cv2.createTrackbar('R','Matrix',0,255,nothing)

while(True):
    # Capture frame-by-frame
    window = np.ones((768,1366,3),'uint8')*255
    
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    
    thumbnail1 = cv2.resize(frame, (640//2, 480//2), interpolation = cv2.INTER_AREA)
    x1 = thumbnail1.shape[0]
    y1 = thumbnail1.shape[1]
    
    
    thumbnail = cv2.resize(gray, (640//10, 480//10), interpolation = cv2.INTER_AREA)
    
    maks = np.max(thumbnail)
    mins = np.min(thumbnail)
    
    x = thumbnail.shape[0]
    y = thumbnail.shape[1]
    
    thumbnail = ((thumbnail-mins)/(maks-mins))*255
    
    font = cv2.FONT_HERSHEY_DUPLEX
    cv2.imshow('Matrix',window)
    
    r = cv2.getTrackbarPos('R','Matrix')
    
    
    time.sleep(r/25)
    
    for i in range(y):
        for j in range(x):
            cv2.putText(window,str(int(thumbnail[j][i])),(((i*(1366//y)+10),(j*(768//x)))), font, 0.3,(50,50,50),1,cv2.LINE_AA)

    # Display the resulting frame
    
    window [0:x1,0:y1] = thumbnail1

    cv2.imshow('Matrix',window)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()