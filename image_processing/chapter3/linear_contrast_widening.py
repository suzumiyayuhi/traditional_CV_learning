import cv2
import numpy as np


def LinearContrastWidening(img, fa, fb, ga, gb):
    alpha = ga / fa
    beta = (gb - ga) / (fb - fa)
    gamma = (255 - gb) / (255 - fb)
    for i in range(0, len(img)):
        for j in range(0, len(img[0, :])):
            if 0 <= img[i][j] < fa:
                img[i][j] = alpha * img[i][j]
            elif fa <= img[i][j] < fb:
                img[i][j] = beta * (img[i][j] - fa) + ga
            elif fb <= img[i][j] < 255:
                img[i][j] = gamma * (img[i][j] - fb) + gb
    return img


temImg = cv2.imread("../images/12.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
print(np.shape(temImg))
#print(len(temImg[0, :]))
temImg = LinearContrastWidening(temImg, 50, 200, 100, 140)
cv2.imwrite("../images/12.jpg", temImg)
cv2.imshow("img", temImg)
cv2.waitKey()