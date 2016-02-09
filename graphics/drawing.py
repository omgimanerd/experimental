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

  def stroke_circle(self, cx, cy, r, color, thickness):
    self.picture.map(Transformation.circle_stroke_lambda(
      cx, cy, r, color, thickness))

  def fill_circle(self, cx, cy, r, color):
    self.picture.map(Transformation.circle_fill_lambda(cx, cy, r, color))

  def generate(self):
    self.picture.generate()
