import cv2
import numpy
import math
import tools.AddNoise

import numpy as np


def MedianFiltering_3x3(img):
    out = img
    dire = [[-1, -1],
            [-1, 0],
            [-1, 1],
            [0, -1],
            [0, 0],
            [0, 1],
            [1, -1],
            [1, 0],
            [1, -1]]
    for i in range(1, img.shape[0] - 1):
        for j in range(1, img.shape[1] - 1):
            temArray = []
            for k in range(0, 9):
                for l in range(0, 1):
                    temArray.append(img[i + dire[k][l]][j + dire[k][l]])
            temMedian = np.median(temArray)
            out[i][j] = temMedian
    return out


temImg = cv2.imread("../images/gray_sunflower.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
#temImg = tools.AddNoise.AddGaussianNoise(temImg, 0.01, 0.01)
temImg = tools.AddNoise.AddSaltPepperNoise(temImg, 0.01)
cv2.imshow("tem", temImg)
cv2.waitKey()
temImg = MedianFiltering_3x3(temImg)
cv2.imshow("tem", temImg)
cv2.waitKey()
