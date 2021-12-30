import cv2
import numpy as np


def HistogramEqualization(img):
    y = len(img)
    x = len(img[0, :])
    n = x * y
    temSum = np.zeros(256)
    for i in range(0, y):
        for j in range(0, x):
            temGrayLevel = img[i][j]
            temSum[temGrayLevel] = temSum[temGrayLevel] + 1
    for i in range(1, 256):
        temSum[i] = temSum[i] + temSum[i - 1]
    for i in range(0, y):
        for j in range(0, x):
            img[i][j] = 255 * temSum[img[i][j]] / n
            img[i][j] = round(img[i][j])
    return img


temImg = cv2.imread("../images/12.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
temImg = HistogramEqualization(temImg)
cv2.imshow("img", temImg)
cv2.waitKey()
#cv2.imwrite("../images/12.jpg", temImg)

