import cv2
import math
import numpy as np


def NonlinearDynamicAdjust(img):
    c = 255 / math.log(256)
    print(c)
    for i in range(0, len(img)):
        for j in range(0, len(img[0, :])):
            img[i][j] = c * math.log(1 + img[i][j])
    return img


temImg = cv2.imread("../images/elder_scroll_dim_room_gray_240p.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
temImg = NonlinearDynamicAdjust(temImg)
cv2.imshow("img", temImg)
cv2.waitKey()
#cv2.imwrite("../images/12.jpg", temImg)
