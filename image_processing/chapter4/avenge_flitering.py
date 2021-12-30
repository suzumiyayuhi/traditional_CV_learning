import cv2
import numpy as np
import tools.AddNoise


def AvengeFiltering_3x3(img):
    out = img
    for i in range(1, img.shape[0] - 1):
        for j in range(1, img.shape[1] - 1):
            avg_sum = int(img[i - 1][j - 1]) + int(img[i - 1][j]) + int(img[i - 1][j + 1]) + int(img[i][j - 1]) + int(img[i][j]) + int(img[i][j + 1]) + int(img[i + 1][j - 1]) + int(img[i + 1][j]) + int(img[i + 1][j + 1])
            out[i][j] = round(avg_sum / 9)
#           print(avg_sum)
    return out


temImg = cv2.imread("../images/gray_sunflower.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)

'''temImg1 = tools.AddNoise.AddSaltPepperNoise(temImg, 0.08)
cv2.imshow("tem", temImg1)
cv2.waitKey()
temImg1 = AvengeFiltering_3x3(temImg)
cv2.imshow("tem", temImg1)
cv2.waitKey()'''

temImg2 = tools.AddNoise.AddGaussianNoise(temImg, 0.01, 0.01)
cv2.imshow("tem", temImg2)
cv2.waitKey()
temImg2 = AvengeFiltering_3x3(temImg)
cv2.imshow("tem", temImg2)
cv2.waitKey()


