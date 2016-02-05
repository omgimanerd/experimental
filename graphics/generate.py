#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

from picture import Picture
from drawing import Drawing

import math

def main():
  p = Picture("test.ppm", 500, 500)
  p.map(Drawing.line_lambda(-5, 2, 3, [128, 0, 0], 10))
  p.generate()

if __name__ == "__main__":
  main()
