#!/usr/bin/python

def mathop(n):
  return (n + 488) / (9000 * 758)

def names(n):
  i = 0
  while i < n:
    print "Alvin"
    i += 1

def countBy5(n):
  i = 0
  while i < n:
    if (i % 5 == 0):
      print i
    i += 1

def numberSign(n):
  if n > 0:
    return "+"
  elif n < 0:
    return "-"
  return "0"

def round(n):
  return int(n + 0.5)

def factorial(n):
  i = 1
  while n > 1:
    i *= n
    n -= 1
  return i
