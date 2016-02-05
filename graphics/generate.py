#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

from picture import Picture

import math

def change(current, dimens, color):
  if current[0] > dimens[0] / 2:
    return [100, 100, 100]
  return color

def is_on_line(a, b, c, px, py):
  return (abs(px * a + py * b + c) / math.sqrt(a * a + b * b)) < 5

def line(current, dimens, color):
  if is_on_line(5, -2, -3, current[0], current[1]):
    return [128, 0, 0]
  return color

def main():
  p = Picture("test.ppm", 500, 500)
  p.map(line)
  p.generate()

if __name__ == "__main__":
    main()
