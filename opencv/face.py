#!/usr/bin/env python3

import cv2
import numpy as np

capture = cv2.VideoCapture(0)

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

while(True):
    ret, frame = capture.read()
    faces = face_cascade.detectMultiScale(frame, 1.3, 5)
    roi = None
    for (x, y, w, h) in faces:
        xStart = int(x + w / 4)
        xEnd = int(x + 3 * w / 4)
        frame = cv2.rectangle(frame, (xStart, y), (xEnd, y+int(h/3)), (255, 0, 0), 2)
        roi = frame[y:y+int(h/3), xStart:xEnd, 0]
        for d in roi:
            print(d)
    if roi is not None:
        break
    
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

capture.release()
cv2.destroyAllWindows()
