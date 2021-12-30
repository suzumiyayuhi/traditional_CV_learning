import cv2
import numpy as np
import math

dire = [[-1, 1],
        [0, 1],
        [1, 1],
        [-1, 0],
        [0, 0],
        [1, 0],
        [-1, -1],
        [0, -1],
        [1, -1]]


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
    out = np.zeros([np.shape(img)[0] - int(kernelSize/2), np.shape(img)[1] - int(kernelSize/2)])
    for i in range(int(kernelSize/2), np.shape(img)[0] - int(kernelSize/2)):
        for j in range(int(kernelSize/2), np.shape(img)[1] - int(kernelSize/2)):
            temSum = 0
            for k in range(0, kernelSize):
                for l in range(0, kernelSize):
                    temSum = temSum + img[i - int(kernelSize/2) + k][j - int(kernelSize/2) + l] * filterTemplate[k][l]
            out[i][j] = int(temSum)
    out = np.clip(out, 0, 255)
    out = np.uint8(out)
    print(out)
    return out


def PrewittOperator(img, threshold):
    Prewitt_x = [[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]]
    Prewitt_y = [[1, 1, 1], [0, 0, 0], [-1, -1, -1]]
    out = np.zeros(np.shape(img))
    out_x = out
    out_y = out
    for i in range(1, img.shape[0] - 1):
        for j in range(1, img.shape[1] - 1):
            temSum_x = 0
            temSum_y = 0
            for k in range(0, 3):
                for l in range(0, 3):
                    temSum_x = temSum_x + Prewitt_x[k][l] * int(img[i+k-1][j+l-1])
                    temSum_y = temSum_y + Prewitt_y[k][l] * int(img[i+k-1][j+l-1])
            temSum_x = temSum_x * temSum_x
            temSum_y = temSum_y * temSum_y
            temSum = temSum_x + temSum_y
            out_x[i][j] = math.sqrt(temSum_x)
            out_y[i][j] = math.sqrt(temSum_y)
            out[i][j] = math.sqrt(temSum)

    out_x = np.uint8(out_x)
    out_y = np.uint8(out_y)
    out = np.uint8(out)

    out_x = np.clip(out_x, 0, 255)
    out_y = np.clip(out_y, 0, 255)
    out = np.clip(out, 0, 255)
    ''''''
    for i in range(1, img.shape[0] - 1):
        for j in range(1, img.shape[1] - 1):
            if threshold < out[i][j]:
                out[i][j] = 0
            else:
                out[i][j] = 255
            if threshold < out_x[i][j]:
                out_x[i][j] = 0
            else:
                out_x[i][j] = 255
            if threshold < out_y[i][j]:
                out_y[i][j] = 0
            else:
                out_y[i][j] = 255

    '''
    img2 = cv2.Prewitt(img, cv2.CV_16S, 1, 1)
    img2 = cv2.convertScaleAbs(img2)
    cv2.imshow("img2", img2)
    '''

    '''
    cv2.imshow("out_y", out_y)
    cv2.imshow("out_x", out_x)
    cv2.imshow("out", out)
    cv2.imshow("img2", img2)
    cv2.waitKey()
    '''
    return [out_x, out_y, out]


def CannyEdgeDetection(img, kernelSize, sigma, threshold):
    out = img
    lev = img
    theta = img

    img = GaussFilter(img, kernelSize, sigma)
    [img_x, img_y, img] = PrewittOperator(img, threshold)

#    img_x = cv2.Prewitt(img, cv2.CV_16S, 1, 0)
#    img_y = cv2.Prewitt(img, cv2.CV_16S, 0, 1)
#    img = cv2.Prewitt(img, cv2.CV_16S, 1, 1)
    cv2.imshow("imgx", img_x)
    cv2.imshow("imgy", img_y)
    cv2.imshow("img1", img)
    '''
    cv2.waitKey()
    img_x = np.clip(img_x, 1, 255)
    img_y = np.clip(img_x, 1, 255)
    img = np.clip(img_x, 1, 255)
    '''
    for i in range(1, img.shape[0] - 1):
        for j in range(1, img.shape[1] - 1):
            theta[i][j] = math.atan(int(img_y[i][j]+1) / int(img_x[i][j]+1))
            lev[i][j] = math.sqrt(int(img_x[i][j]) ** 2 + int(img_y[i][j]) ** 2)
#    print(att)
#    print(theta)
    lev = cv2.convertScaleAbs(lev)
    theta = cv2.convertScaleAbs(theta)
    cv2.imshow("lev", lev)
    cv2.imshow("theta", theta)
    cv2.waitKey()

'''
temImg = cv2.imread("images/car_fog_gray.jpg")
#temImg = cv2.imread("images/sunflower_240p_gray.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)

cv2.imshow("img", temImg)
cv2.waitKey()
temImg = GaussFilter(temImg, 3, 3)
cv2.imshow("img", temImg)
cv2.waitKey()
'''
'''
imgs = SobelOperator(temImg, 150)
cv2.imshow("imgx", imgs[0])
cv2.imshow("imgy", imgs[1])
cv2.imshow("img1", imgs[2])
cv2.waitKey()
'''

'''
cv2.imshow("img", temImg)
cv2.waitKey()
'''

''''''
temImg = cv2.imread("images/car_fog_gray.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
CannyEdgeDetection(temImg, 2, 30, 80)

