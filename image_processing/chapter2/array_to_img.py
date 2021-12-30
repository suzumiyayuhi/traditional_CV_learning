import cv2
import matplotlib.pyplot as plt
import numpy as np
import os

'''
randomByteArray = bytearray(os.urandom(36))
flatNumpyArray = np.array(randomByteArray)
grayImage = flatNumpyArray.reshape(6, 6)
print(grayImage)
cv2.imshow("img", grayImage)
'''

temArray = [[100, 76, 0, 132, 7, 7],
            [28, 7, 7, 7, 7, 243],
            [28, 243, 7, 100, 7, 28],
            [100, 7, 7, 0, 7, 100],
            [100, 0, 7, 7, 132, 0],
            [132, 132, 132, 100, 7, 100]]

temArray = np.array(temArray)
img = temArray.reshape(6, 6)

plt.subplot(121)
plt.imshow(img, 'gray')
plt.subplot(122)
plt.hist(img.ravel(), 256, [0, 256])
plt.show()
# cv2.imshow("img", img)
''''''
