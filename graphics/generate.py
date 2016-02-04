#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

from picture import Picture

def main():
  p = Picture("test.ppm", 1000, 1000)
  p.generate()

if __name__ == "__main__":
    main()
