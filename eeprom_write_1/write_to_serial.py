#! /usr/bin/env python2

import sys
import serial
import time

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)

lineNum = 0

time.sleep(10)

ser.write(b'\n')

for p in sys.argv[1:]:
  f = open(p, 'r')
  for line in f:
    s = str(lineNum) + " " + line

    success = False
    while not success:
      print "send", s
      ser.write(s.encode())

      # time.sleep(0.005)

      res = ser.readline()
      if res == s:
        success = True
      else:
        print "mismatch", res, len(res), len(s)

    lineNum += 1

    # time.sleep(0.5)

  print "file "+p+" ended at "+str(lineNum)

# f = open('workfile', 'w')