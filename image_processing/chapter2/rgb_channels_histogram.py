import cv2
import matplotlib.pyplot as plt

img1 = cv2.imread("../images/sunflower_240p.jpg")
img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2RGB)

hist1 = plt.subplot(241)
hist1.hist(img1[:, :, 0].ravel(), 256, [0, 255], color='r')
hist1.set_ylim([0, 1800])

hist2 = plt.subplot(242)
hist2.hist(img1[:, :, 1].ravel(), 256, [0, 255], color='g')
hist2.set_ylim([0, 1800])

hist3 = plt.subplot(243)
hist3.hist(img1[:, :, 2].ravel(), 256, [0, 255], color='b')
hist3.set_ylim([0, 1800])

originImg1 = plt.subplot(244)
originImg1.imshow(img1)


img2 = cv2.imread("../images/seascape_after_sunset_240p.jpg")
img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2RGB)
hist1 = plt.subplot(245)
hist1.hist(img2[:, :, 0].ravel(), 256, [0, 255], color='r')
hist1.set_ylim([0, 1800])

hist2 = plt.subplot(246)
hist2.hist(img2[:, :, 1].ravel(), 256, [0, 255], color='g')
hist2.set_ylim([0, 1800])

hist3 = plt.subplot(247)
hist3.hist(img2[:, :, 2].ravel(), 256, [0, 255], color='b')
hist3.set_ylim([0, 1800])

originImg2 = plt.subplot(248)
originImg2.imshow(img2)
plt.show()
