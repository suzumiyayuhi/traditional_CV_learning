import tools.ImgResize
import tools.ConvToGray
import cv2
import numpy as np
import matplotlib.pyplot as plt

#temImg = cv2.imread("../images/elder_scroll_dim_room_gray_240p.jpg")
'''
temImg = cv2.imread(".../images/sunflower_240p_gray.jpg")
temImg = cv2.imread(".../images/sunflower_240p.jpg")
print(np.shape(temImg))
'''

#tools.ImgResize.Convt240P("../images/elder_scroll_dim_room_gray.jpg")

'''
temImg = cv2.imread("../images/sunflower_240p_gray.jpg")
temImg = cv2.cvtColor(temImg, cv2.COLOR_BGR2GRAY)
print(len(temImg))
print()
print(len(temImg[0, :]))
'''

img = cv2.imread("../images/elder_scroll_dim_room_gray_240p.jpg")
img2 = cv2.imread("../images/elder_scroll_dim_room_gray_240p_he.jpg")
'''
cv2.imshow("himawari", img)
cv2.waitKey()
'''
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

hist1 = plt.subplot(121)
hist1.hist(img.ravel(), 256, [0, 256])
hist1.set_ylim([0, 8000])
hist2 = plt.subplot(122)
hist2.hist(img2.ravel(), 256, [0, 256])
hist2.set_ylim([0, 8000])
plt.show()

