#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

HEADER = "P3 %d %d %d\n"

class Picture():
  def __init__(self, filename, width, height, max_color_value=255):
    self.filename = filename
    self.width = width
    self.height = height
    self.max_color_value = max_color_value
    
    self.grid = []
    for y in range(0, height):
      row = []
      for x in range(0, width):
        row.append([0, 0, 0])
      self.grid.append(row)

  def map(function):
    self.grid = map(function, self.grid)
      
  def generate(self):
    with open(self.filename, "w") as picture:
      picture.write(HEADER % (self.width, self.height, self.max_color_value))
      for row in self.grid:
        for pixel in row:
          for color in pixel:
            picture.write("%d " % color)

