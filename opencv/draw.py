#!/usr/bin/env python3


import numpy as np
import cv2

# Create a black image
img = np.zeros((512,512,3), np.uint8)

# Draw a diagonal blue line with thickness of 5 px
img = cv2.line(img,(0,0),(511,511),(255,0,0),5)

img = cv2.rectangle(img, (100,100), (400,130), (0,255,0), 1)

cv2.imshow('image', img)
cv2.waitKey(0)
