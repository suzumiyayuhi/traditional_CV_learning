import cv2
import numpy as np
import math


def Retinex(img, c):
    for i in range(0, len(img)):
        for j in range(0, len(img[0, :])):
            img[i][j] = math.log(img[i][j]) - math.log()

