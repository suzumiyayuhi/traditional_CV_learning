import cv2
import matplotlib.pyplot as plt
import numpy as np

img = cv2.imread("../images/sunflower.jpg")

'''
cv2.imshow("himawari", img)
cv2.waitKey()
'''
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imwrite("../images/gray_sunflower.jpg", img)
cv2.imshow("himawari", img)
cv2.waitKey()

plt.hist(img.ravel(), 256, [0, 256])
plt.show()

