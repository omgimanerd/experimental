#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)
# This is a class that contains drawing methods applied to the Picture class.

from util import Util

class Transformation():
  @staticmethod
  def line_lambda(a, b, c, line_color, thickness):
    return lambda current, dimens, current_color: (
      line_color if Util.is_point_on_line(
        a, b, c, current[0], current[1], thickness / 2) else current_color
    )

  @staticmethod
  def circle_stroke_lambda(cx, cy, r, circle_color, thickness):
    return lambda current, dimens, current_color: (
      circle_color if Util.is_point_on_circle(
        cx, cy, r, current[0], current[1], thickness / 2) else current_color
    )

  @staticmethod
  def circle_fill_lambda(cx, cy, r, circle_color):
    return lambda current, dimens, current_color: (
      circle_color if Util.is_point_in_circle(
        cx, cy, r, current[0], current[1]) else current_color
    )
