#!/usr/bin/python

import random
import sys

def randomize(a):
  for i in range(len(a)):
    randIndex = random.randrange(i, len(a))
    if randIndex == i:
      continue
    tmp = a[i]
    a[i] = a[randIndex]
    a[randIndex] = tmp


q = []
missing = random.randrange(0, 1000)
for i in range(1000):
  if i == missing:
    continue
  q.append(i)

randomize(q)

out = ""
for i in q:
  out += str(i) + "\n"

file = open(sys.argv[1], "wb+")
file.write(out[:-1])
