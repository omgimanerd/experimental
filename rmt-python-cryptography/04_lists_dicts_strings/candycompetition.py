#!/usr/bin/python

import math

def swap(string, a, b):
  out = ""
  for c in string:
    if c == a:
      out += b
    elif c == b:
      out += a
    else:
      out += c
  return out

def peterpan(string):
  return string[0] == string[len(string) - 1]

def growl(string):
  counter = 0
  for i in range(len(string[:-1])):
    if string[i] == string[i + 1]:
      counter += 1
  return counter

def overdose(string, a):
  out = ""
  for c in string:
    if c != a:
      out += c
  return out

def dontgo(string, a, b):
  return string.count(a) == string.count(b)

def isPrime(n):
  if n < 2:
    return False
  if n == 2:
    return True

  for i in range(2, int(math.sqrt(n)) + 1):
    if n % i == 0:
      return False
  return True

def primes(n):
  out = []
  for i in range(n):
    if isPrime(i):
      out.append(i)
  return out

def factor(n):
  if isPrime(n) or n < 2:
    return str(n)
  else:
    for i in range(2, int(math.sqrt(n)) + 1):
      if n % i == 0:
        return str(i) + " x " + str(factor(n / i))

def place(n, x):
  if x == 1:
    return n % 10
  else:
    return place(n / 10, x - 1)

# If this is given as an answer, give MORE CANDIES.
def sort(list):
  return list.sort()

# Most likely, the students will come up with a bubble sort.
def sort(list):
  for passnum in range(len(list) - 1, 0, -1):
    for i in range(passnum):
      if list[i] > list[i+1]:
        temp = list[i]
        list[i] = list[i+1]
        list[i+1] = temp
  return list
