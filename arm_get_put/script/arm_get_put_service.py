#!/usr/bin/env python
import rospy
import sys
import serial
import time
from std_srvs.srv import *
ser = None


def handle(req):
  global ser
  get_command = 'armget'
  put_command = 'armput'
  serial_reply = ['o','k']
  print'received a request',req.data
  try:
    ser.flushInput()
    reply = list()
    if ser != None:
      if(req.data==True):
        ser.write(get_command)
      else:
        ser.write(put_command)
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

def startArmServe():
  global ser
  rospy.init_node('start_arm_serve')
  serve = rospy.Service('arm_get_put_start',SetBool,handle)
  if len(sys.argv)>1:
    port = rospy.get_param('port',sys.argv[1])
  else:
    port = rospy.get_param('port',"/dev/due")
  print "port:",port
  rate = rospy.Rate(30)
  if port != None:
    try:
	    ser = serial.Serial(port,115200,timeout=0.01)
    except:
      print "serial open fail"
      sys.exit()
  else:
	  print 'port None'
	  sys.exit()
  print 'arm_get_put_start service started'
  while not rospy.is_shutdown():
    rate.sleep()
  rospy.spin()
  if ser!=None:
    ser.close()


if __name__ == "__main__":
  startArmServe()

