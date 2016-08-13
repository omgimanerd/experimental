#!/usr/bin/python

import sys

fromChar = "abcdefghijklmnopqrstuvwxyz"
toChar = "qpwoeirutyalskdjfhgzmxncbv"

def encode(filename):
  f = open(filename)
  data = f.read().lower()
  f.close()
  print data

  out = ""
  for i in data:
    if i in fromChar:
      out += toChar[fromChar.index(i)]
    else:
      out += i

  f = open(filename, "wb+")
  f.write(out)
  return out

print encode(sys.argv[1])
