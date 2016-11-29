import time
import grovepi
import sys
import os
import fcntl
from picamera import PiCamera

pir_sensor = 8
fl = fcntl.fcntl(sys.stdin.fileno(), fcntl.F_GETFL)
fcntl.fcntl(sys.stdin.fileno(), fcntl.F_SETFL, fl | os.O_NONBLOCK)

grovepi.pinMode(pir_sensor, "INPUT")
camera = PiCamera()
flag = 0
while flag == 0:
	try:
		if grovepi.digitalRead(pir_sensor):
			camera.start_preview()
			time.sleep(2)
			camera.capture('image.jpg')
			camera.stop_preview()
		flag = sys.stdin.read()
		time.sleep(2)
	except IOError:
		print "Error"
				

