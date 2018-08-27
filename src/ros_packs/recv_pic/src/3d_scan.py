#!/usr/bin/env python
import numpy as np
import serial           
import sys

try:
	ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=0.5)
except Exception, e:
	print 'open serial failed.'
	exit(0)

init = 0
while True:
	s = ser.read()
	if s == b'\xFF':
		init += 1
	else:
		init = 0
	if init == 4:
		b1 = str(ser.read())
		b2 = str(ser.read())
		i = np.frombuffer(b1+b2, np.int16)
		if i < -180 or i > 180:
			continue
		print str(i), 
		print str(np.frombuffer(str(ser.read()) + str(ser.read()), np.uint16))