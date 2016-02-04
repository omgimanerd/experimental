#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

from picture import Picture

def change(current, dimens, color):
  if current[0] > dimens[0] / 2:
    return [100, 100, 100]
  return color

def main():
  p = Picture("test.ppm", 500, 500)
  p.map(change)
  p.generate()

if __name__ == "__main__":
    main()
