#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

import random

from drawing import Drawing
from color import Color

def main():
  p = Drawing("test.ppm", 400, 400)
  p.stroke_circle(250, 250, 30, Color("#FF00FF"), 3)
  p.fill_circle(100, 100, 40, Color("#ABABF3"))
  p.generate()

if __name__ == "__main__":
  main()
