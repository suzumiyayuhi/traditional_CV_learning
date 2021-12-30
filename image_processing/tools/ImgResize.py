import cv2


def Convt240P(inputImgPath):
    flag = 0
    temSize = len(inputImgPath)
    while temSize >= 0:
        flag = 1
        temSize = temSize - 1
        if inputImgPath[temSize] == '.':
            flag = 2
            break
    if flag == 0:
        print("error")
        return
    outputImagePath = inputImgPath[0:temSize]
    outputImagePath = outputImagePath + "_240p.jpg"

    img = cv2.imread(inputImgPath)
    outputImage = cv2.resize(img, (320, 240))

    cv2.imwrite(outputImagePath, outputImage)



Convt240P("../images/coins.png")