import cv2


def ConvToGray(inputImgPath):
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
    outputImagePath = outputImagePath + "_gray.jpg"
    print(outputImagePath)
    img = cv2.imread(inputImgPath, cv2.IMREAD_GRAYSCALE)

   # outputImage = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    outputImage = img
    cv2.imwrite(outputImagePath, outputImage)

ConvToGray("../images/car_fog.png")