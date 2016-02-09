#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)
# This is a class that manages colors for the Picture and Drawing class.

class Color:
  def __init__(self, hex_code):
    """
    Constructor for a Color class.

    Parameters:
    hex_code: string, the hexadecimal representation of the color
    """
    self.color = self.__hex_to_rgb__(hex_code)
    self.counter = 0

  def __iter__(self):
    return self
    
  def __len__(self):
    return len(self.color)

  @staticmethod
  def __hex_to_rgb__(hex_code):
    """
    Given the hexdecimal representation of a color, this returns the rgb
    representation of the given color.

    Parameters:
    hex_code: string, the hex code to convert to rgb 

    http://stackoverflow.com/questions/214359/converting-hex-color-to-rgb-and-vice-versa
    """
    hex_code = hex_code.lstrip('#')
    lv = len(hex_code)
    return [int(hex_code[i:i + lv // 3], 16) for i in range(0, lv, lv // 3)]

  def next(self):
    if self.counter == 3:
      self.counter = 0
      raise StopIteration
    color = self.color[self.counter]
    self.counter += 1
    return color

if __name__ == "__main__":
  c = Color("#FFFC3F")
  print len(c)
  for a in Color("ABCDEF"):
    print a
