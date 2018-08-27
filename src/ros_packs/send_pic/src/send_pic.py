#!/usr/bin/env python
import rospy
from std_msgs.msg import Header
from sensor_msgs.msg import Image
from picamera import PiCamera
import os
import cv2
import numpy as np
import time

IMAGE_WIDTH = 320
IMAGE_HEIGHT = 240

camera = PiCamera()
camera.resolution = (IMAGE_WIDTH, IMAGE_HEIGHT)
camera.framerate = 24

rospy.init_node("send_pic", anonymous=True)
image_pubulish = rospy.Publisher('/camera/image_raw', Image, queue_size=1)
rospy.loginfo("Loading...")
rate = rospy.Rate(30)
try:
	camera.start_preview()
	while not rospy.is_shutdown():
		imgdata = np.empty((IMAGE_WIDTH * IMAGE_HEIGHT * 3,), dtype=np.uint8)
		camera.capture(imgdata, 'bgr', use_video_port=True)
		image_temp = Image()
		header = Header(stamp=rospy.Time.now())
		header.frame_id = 'map'
		image_temp.height = IMAGE_HEIGHT
		image_temp.width = IMAGE_WIDTH
		image_temp.encoding='bgr8'
		image_temp.data = np.array(imgdata).tostring()
		image_temp.header = header
		image_temp.step = IMAGE_WIDTH * 3
		image_pubulish.publish(image_temp)
		rospy.loginfo("Sending Frame...")
		rate.sleep()
	pass
finally:
	camera.close()