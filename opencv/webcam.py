#!/usr/bin/python

import cv2

def display_webcam():
    cap = cv2.VideoCapture(0)

    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        print frame
        print dir(frame)

        # Our operations on the frame come here
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Display the resulting frame
        cv2.imshow('frame',gray)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    capture = cv2.VideoCapture(0)
    ret, frame = capture.read()

    for i in frame[0]:
        print i


    print len(frame)
    print len(frame[0])

    capture.release()
