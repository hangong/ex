import cv2 as cv
import numpy as np

data=np.genfromtxt('test.csv', delimiter=',',skip_header=1)

data_cm = np.array([]);
cv.reduce(data,data_cm,1,op = cv.CV_REDUCE_AVG)
print data_cm


#gray = np.float32(gray)
#dst = cv2.cornerHarris(gray,2,3,0.04)

