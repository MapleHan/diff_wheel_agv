#!/usr/bin/env python
import rospy
import sys
import serial
import time
from std_srvs.srv import *
ser = None


def handle(req):
  global ser
  up_command = 'liftingup'
  down_command = 'liftingdown'
  serial_reply = ['o','k']
  print'received a request',req.data
  try:
      ser.flushInput()
      reply = list()
      if ser != None:
          if(req.data==True):
              ser.write(up_command)
          else:
              ser.write(down_command)
          bt = time.time()
          while (time.time()-bt)<0.1 and len(reply)<len(serial_reply):
              if ser.inWaiting():
                  reply.append(ser.read())
          if reply[0:len(reply)]==serial_reply[0:len(serial_reply)]:
              print reply
              return([True,'drive_received_command'])
  except:
      pass
  print reply
  return([False,'drive lost'])

def startLiftingServe():
	global ser
	rospy.init_node('start_lifting_serve')
	serve = rospy.Service('lifting_start',SetBool,handle)
	port = rospy.get_param('port',sys.argv[1])
	print port
        rate = rospy.Rate(30)
	if port != None:
		ser = serial.Serial(port,115200,timeout=0.01)
	else:
		print 'port None'
		sys.exit()
	print 'lifting service started'
        while not rospy.is_shutdown():
            rate.sleep()
	rospy.spin()
        if ser!=None:
            ser.close()
            print 'sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss'
if __name__ == "__main__":
    startLiftingServe()

