import cv2
import math
import numpy as np

'''temImg = cv2.imread("images/zi.png")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
temImg = cv2.Sobel(temImg, cv2.CV_16S, 1, 1)
temImg = cv2.convertScaleAbs(temImg)
cv2.imshow("img", temImg)
cv2.waitKey()'''

'''tem1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
tem2 = [[9, 8, 7], [6, 5, 4], [3, 2, 1]]
tem1 = np.array(tem1)
tem2 = np.array(tem2)
print(tem1)
print(tem2)'''



def GaussTemplate(kernelSize, sigma):
    tem = int(kernelSize / 2)
    out = np.zeros([kernelSize, kernelSize])
    temSum = 0
    for i in range(0, kernelSize):
        x2 = (i - tem) ** 2
        for j in range(0, kernelSize):
            y2 = (j - tem) ** 2
            out[i][j] = math.exp(-(x2 + y2) / 2 / sigma / sigma) / 2 / math.pi / sigma / sigma
            temSum = temSum + out[i][j]
    for i in range(0, kernelSize):
        for j in range(0, kernelSize):
            out[i][j] = out[i][j] / temSum
    return out


def GaussFilter(img, kernelSize, sigma):
    filterTemplate = GaussTemplate(kernelSize, sigma)
    out = np.zeros(np.shape(img))
    for i in range(int(kernelSize/2), np.shape(img)[0] - int(kernelSize/2)):
        for j in range(int(kernelSize/2), np.shape(img)[1] - int(kernelSize/2)):
            out[i][j] = img[i][j] * filterTemplate[i][j]

    out = img + out * 30
    print(out)
    out = np.clip(out, 0, 255)
    out = np.uint8(out)
    print(out)
    return out


temImg = cv2.imread("images/coins_square.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
cv2.imshow("img1", temImg)
temImg2 = GaussFilter(temImg, 240, 30)
cv2.imshow("img2", temImg2)
cv2.waitKey()