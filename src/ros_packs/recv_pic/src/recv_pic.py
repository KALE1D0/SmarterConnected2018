#!/usr/bin/env python
import rospy
import cv2
import numpy as np
import time
from sensor_msgs.msg import Image

IMAGE_WIDTH = 320
IMAGE_HEIGHT = 240

def callback(data):
	cv_image = np.fromstring(data.data, dtype=np.uint8)
	cv_image = cv_image.reshape((IMAGE_HEIGHT, IMAGE_WIDTH , 3))

	w = cv_image.shape[1]
	h = cv_image.shape[0]
	ii = 0
	for xi in range(0,w):
		for xj in range(0,h):
			k = 1
			cv_image[xj,xi,0] = int(cv_image[xj,xi,0] * k)
			cv_image[xj,xi,1] = int(cv_image[xj,xi,1] * k)
			cv_image[xj,xi,2] = int(cv_image[xj,xi,2] * k)
	image = cv_image
	cv2.imshow("Image", image)
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	gauss = cv2.GaussianBlur(gray,(3,3),0) 
	canny = cv2.Canny(gauss, 0, 50) 
	cv2.imshow("Canny",canny)
	cv2.waitKey(20)

'''cv2.namedWindow('img')
cv2.imshow('img',img)
cv2.waitKey()
cv2.destroyAllWindows()'''


'''

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imshow("Gray", gray)

gauss = cv2.GaussianBlur(gray,(3,3),0) 
cv2.imshow("Gauss", gauss)

kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3, 3))
erosion = cv2.erode(gauss, kernel,iterations = 1)
cv2.imshow("Erosion", erosion)

dilation = cv2.dilate(erosion,kernel,iterations = 2) 
cv2.imshow("Deliation", dilation)



canny = cv2.Canny(gauss, 0, 30)  
cv2.imshow("Canny",canny)
cv2.waitKey(0)


	cv2.imshow("Raw", cv_image)
	cv2.waitKey(20)

	gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
	cv2.imshow("Gray", gray)
	cv2.waitKey(20)

	gauss = cv2.GaussianBlur(gray,(3,3),0) 
	cv2.imshow("Gauss",gauss)
	cv2.waitKey(20)

	kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3, 3))
	erosion = cv2.erode(cv_image, kernel,iterations = 1)
	dilation = cv2.dilate(erosion, kernel,iterations = 1) 

	canny = cv2.Canny(dilation, 0, 5)  
	cv2.imshow("canny", canny)
	cv2.waitKey(20)
	##cv2.destroyAllWindows()'''

rospy.init_node('recv_pic', anonymous=True)
image_sub = rospy.Subscriber("/camera/image_raw", Image, callback)
rospy.spin()
