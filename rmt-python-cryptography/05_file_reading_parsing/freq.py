#!/usr/bin/python

import sys

def freq(filename):
  file = open(filename)
  data = file.read().replace("\n", "")
  chars = {}
  for c in data:
    if chars.has_key(c):
      chars[c] += 1
    else:
      chars[c] = 1
  print chars

freq(sys.argv[1])
