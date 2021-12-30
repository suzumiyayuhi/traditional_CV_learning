import random
import numpy as np
import cv2


def AddSaltPepperNoise(img, prob):
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            temRnd1 = random.random()
            temRnd2 = random.random()
            if temRnd1 < prob:
                if temRnd2 > 0.5:
                    img[i][j] = 0
                else:
                    img[i][j] = 255
    '''cv2.imshow("img", img)
    cv2.waitKey()'''
    return img


def AddGaussianNoise(img, mean, var):
    img = np.array(img / 255, dtype=float)
    noise = np.random.normal(mean, var ** 0.5, img.shape)
    img = noise + img
    img = np.clip(img, 0, 1.0)
    img = np.uint8(img * 255)
    return img


temImg = cv2.imread("../images/gray_sunflower.jpg")
#temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
cv2.imshow("img", temImg)
cv2.waitKey()


temImg = AddSaltPepperNoise(temImg, 0.1)
cv2.imshow("img", temImg)
cv2.waitKey()
'''
temImg = AddGaussianNoise(temImg, 0.01, 0.01)
cv2.imshow("img", temImg)
cv2.waitKey()
'''
