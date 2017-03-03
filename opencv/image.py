#!/usr/bin/env python3

import numpy as np
import cv2

img = cv2.imread('test.png')
karl = img[150:300, 300:500]
img[150:300, 850:1050] = karl
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

corners = cv2.goodFeaturesToTrack(gray, 1000, 0.01, 10)
corners = np.int0(corners)
for i in corners:
    x, y, = i.ravel()
    cv2.circle(img, (x, y), 3, 255, -1)

cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite('lol.png', img)
