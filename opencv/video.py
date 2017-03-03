#!/usr/bin/env python3

import cv2
import numpy as np

capture = cv2.VideoCapture(0)

while(True):
    ret, frame = capture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = np.float32(gray)

    """
    dst = cv2.cornerHarris(gray, 2, 3, 0.04)
    dst = cv2.dilate(dst, None)
    frame[dst > 0.01 * dst.max()] = [0, 0, 255]
    """

    corners = cv2.goodFeaturesToTrack(gray, 50, 0.1, 20)
    corners = np.int0(corners)
    for i in corners:
        x, y = i.ravel()
        cv2.circle(frame, (x, y), 3, 255, -1)
    
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

capture.release()
cv2.destroyAllWindows()
