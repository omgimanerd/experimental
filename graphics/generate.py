#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

import random

from drawing import Drawing

def main():
  p = Drawing("test.ppm", 400, 400)
  p.stroke_circle(250, 250, 30, [128, 0, 0], 3)
  p.fill_circle(100, 100, 40, [128, 0, 0])
  p.fill_circle(120, 120, 10, [0, 128, 0])
  p.generate()

if __name__ == "__main__":
  main()
