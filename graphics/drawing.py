#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)
# This is a class abstracting the Transformation and Picture classes into a
# general Drawing class.

from picture import Picture
from transformation import Transformation

class Drawing():
  def __init__(self, name, width, height):
    self.picture = Picture(name, width, height)
    
  def draw_point(self, x, y, color):
    self.picture.set_pixel(x, y, color)

  def draw_line(self, x1, y1, x2, y2, color, thickness):
    """
    Values for y = mx + b line formula.
    y = mx + b
    b = y - mx
    """
    m = (y2 - y1) / (x2 - x1)
    b = y1 - (m * x1)
    """
    Values for Ax + By + C = 0 line formula.
    A = delta Y
    B = - delta X
    C = - delta X times b
    """
    A = abs(y2 - y1)
    B = -abs(x2 - x1)
    C = -abs(x2 - x1) * b
    self.picture.map(Transformation.line_lambda(A, B, C, color, thickness),
                     section=[[x1, y1], [x2, y2]])

  def stroke_circle(self, cx, cy, r, color, thickness):
    self.picture.map(Transformation.circle_stroke_lambda(
      cx, cy, r, color, thickness))

  def fill_circle(self, cx, cy, r, color):
    self.picture.map(Transformation.circle_fill_lambda(cx, cy, r, color))

  def generate(self):
    self.picture.generate()
