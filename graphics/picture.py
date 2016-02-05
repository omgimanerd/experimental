#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)
# This is a class that facilitates the generation of a raster ppm image file.

HEADER = "P3 %d %d %d\n"

class Picture():
  def __init__(self, filename, width, height, max_color_value=255):
    """
    Constructor for a Picture class.

    Parameters:
    filename: string, the name of the new image file
    width: number, the width of the image in pixels
    height: number, the height of the image in pixels
    max_color_value: the max color value of the ppm, defaults to 255
    """
    self.filename = filename
    self.width = width
    self.height = height
    self.max_color_value = max_color_value
    
    self.grid = []
    for y in range(0, height):
      self.grid.append([[0, 0, 0] for x in range(width)])

  def map(self, function):
    """
    Applies the given function transformation to every pixel in the grid.
    
    Parameters:
    function: function([currentX, currentY], [width, height],
                       [currentR, currentG, currentB])
    """
    for y in range(0, self.height):
      for x in range(0, self.width):
        self.grid[x][y] = function([x, y], [self.width, self.height],
                                   self.grid[x][y])
      
  def generate(self):
    """
    Turns the internal raster into a ppm image file and generates the file.
    """
    with open(self.filename, "w") as picture:
      picture.write(HEADER % (self.width, self.height, self.max_color_value))
      for row in self.grid:
        for pixel in row:
          for color in pixel:
            picture.write("%d " % color)
