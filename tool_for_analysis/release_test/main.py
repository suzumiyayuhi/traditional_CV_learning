import cv2
import numpy as np
import math
import matplotlib.pyplot as plt
import sys
import ctypes
#!/usr/bin/python
#-*- coding:cp936 -*-

BASE_DIR = "../../images\\"

BASE_DIR_02 = BASE_DIR + "02\\"
BASE_DIR_02_SBC = BASE_DIR_02 + "sorted_by_classes\\"
DIR_02_SRC_CORNERFRACTURE = BASE_DIR_02_SBC + "cornerfracture\\"
DIR_02_SRC_CRACK = BASE_DIR_02_SBC + "crack\\"
DIR_02_SRC_HOLE = BASE_DIR_02_SBC + "hole\\"
DIR_02_SRC_PATCH = BASE_DIR_02_SBC + "patch\\"
DIR_02_SRC_REPAIR = BASE_DIR_02_SBC + "repair\\"
DIR_02_SRC_SEAMBROKEN = BASE_DIR_02_SBC + "seambroken\\"
DIR_02_SRC_SLAB = BASE_DIR_02_SBC + "slab\\"
DIR_02_SRC_TRACK = BASE_DIR_02_SBC + "track\\"
DIR_02_SRC_VM = BASE_DIR_02 + "visualized_mask\\"

BASE_DIR_04 = BASE_DIR + "04\\"
DIR_04_SRC_TRAIN = BASE_DIR_04 + "train\\"
DIR_04_SRC_VAL = BASE_DIR_04 + "val_fixed\\"
DIR_04_SRC_TRAIN_LABEL = BASE_DIR_04 + "label_grey\\train\\"
DIR_04_SRC_VAL_LABEL = BASE_DIR_04 + "label_grey\\val\\"

BASE_DIR_05 = BASE_DIR + "05\\"
DIR_05_SRC_JOINT = BASE_DIR_05 + "joint\\"					#板缝
DIR_05_SRC_MARKING = BASE_DIR_05 + "marking\\"				#标线
DIR_05_SRC_SCRATCH = BASE_DIR_05 + "scratch\\"				#划痕
DIR_05_SRC_STAIN = BASE_DIR_05 + "stain\\"						#油渍
BASE_DIR_05_SORT_BY_FEATURE = BASE_DIR_05 + "SBF\\"				#根据视觉特征细分
DIR_05_SRC_SBF_JOINT = BASE_DIR_05_SORT_BY_FEATURE + "joint\\"	#板缝
DIR_05_SRC_SBF_MARKING = BASE_DIR_05_SORT_BY_FEATURE + "marking\\"	#标线
DIR_05_SRC_SBF_LONG_BAR = BASE_DIR_05_SORT_BY_FEATURE + "long_bar\\" #大长条(油渍_划痕)
DIR_05_SRC_SBF_GROUND_LIGHT = BASE_DIR_05_SORT_BY_FEATURE + "ground_light\\" #地灯边缘
DIR_05_SRC_SBF_SCRATCH = BASE_DIR_05_SORT_BY_FEATURE + "scratch\\"	#划痕
DIR_05_SRC_SBF_TAD_POLE = BASE_DIR_05_SORT_BY_FEATURE + "tadpole\\"#蝌蚪状油渍



def showGrayHist(srcImagePath, flag=0):
	"""
	:param srcImagePath:原图路径
	:param flag: 0显示所有图，1只显示灰度直方图，2不显示图
	:return:
	"""
	img = cv2.imread(srcImagePath)
	img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	if flag == 2:
		return
	if flag == 1:
		plt.hist(img.ravel(), 256, [0, 256])
		plt.show()
		return
	cv2.imshow("ori", img)
	cv2.waitKey()
	plt.hist(img.ravel(), 256, [0, 256])
	plt.show()


def ctypeTest():
	#pDLL = ctypes.CDLL("AlgorithmTestDLL.dll")
	#pDLL.testHelloWorld()

	''''''
	pDLL = ctypes.CDLL("AlgorithmTestDLL.dll")
	arg1 = ctypes.c_char_p(bytes(DIR_05_SRC_SBF_SCRATCH, 'utf-8'))
	pDLL.testArg.restype = ctypes.c_char_p
	res = pDLL.testArg(arg1)
	print(res.decode('utf-8'))



def getImgShowHist(dirPath):
	pDLL = ctypes.CDLL("AlgorithmTestDLL.dll")
	arg1 = ctypes.c_char_p(bytes(dirPath, 'utf-8'))
	pDLL.getCstrFromVec.restype = ctypes.c_char_p
	res = pDLL.getCstrFromVec(arg1)
	tempath = res.decode('utf-8')
	showGrayHist(tempath)


print(DIR_04_SRC_VAL)
temPath = "../" + DIR_02_SRC_CRACK + "000703_original.bmp"
showGrayHist(temPath, 0)
#getImgShowHist("../" + DIR_04_SRC_VAL)

