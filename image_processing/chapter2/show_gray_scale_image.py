import cv2
import matplotlib.pyplot as plt

img = cv2.imread("../images/sunflower.jpg", 0)

# show gray scale image
'''opencv'''
cv2.imshow("img_gray", img)
cv2.waitKey()

'''plt'''
fig = plt.figure()
ax = fig.add_subplot(121)
ax.imshow(img, cmap="gray")

ax = fig.add_subplot(122)
ax.imshow(img, cmap="gray", vmin=0, vmax=255)
plt.show()
# ------------------------------------------------
