#!/usr/bin/python

import sys

fromChar = "abcdefghijklmnopqrstuvwxyz"
toCharBase = "abcdefghijklmnopqrstuvwxyz"

def encode(filename, offset):
  f = open(filename)
  d = f.read().lower()
  f.close()

  offset = int(offset)
  toChar = toCharBase[offset:] + toCharBase[:offset]

  out = ""
  for c in d:
    if c in fromChar:
      out += toChar[fromChar.index(c)]
    else:
      out += c
  
  f = open(filename, "wb+")
  f.write(out)
  return out

print encode(sys.argv[1], sys.argv[2])
