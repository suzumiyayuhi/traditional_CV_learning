'''from tools import ImgResize

temStr = "../images/seascape_after_sunset.jpg"
ImgResize.Convt240P(temStr)
'''

import os
import cv2 as cv
import numpy as np

# Make an array of 120000 random bytes
randomByteArray = bytearray(os.urandom(100))
# translate into numpy array
flatNumpyArray = np.array(randomByteArray)
# Convert the array to make a 400*300 grayscale image(灰度图像)
grayImage = flatNumpyArray.reshape(10, 10)
# show gray image
cv.imshow('GrayImage', grayImage)
# print image's array
print(grayImage)
cv.waitKey()
# byte array translate into RGB image
randomByteArray1 = bytearray(os.urandom(360000))
flatNumpyArray1 = np.array(randomByteArray1)
BGRimage = flatNumpyArray1.reshape(300,400,3)
cv.imshow('BGRimage', BGRimage)
cv.waitKey()
cv.destroyAllWindows()
