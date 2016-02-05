#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)
# This is a class that contains drawing methods applied to the Picture class.

from picture import Picture
from util import Util

class Drawing():
  @staticmethod
  def line_lambda(a, b, c, line_color, thickness):
    return lambda current, dimens, current_color: (
      line_color if Util.is_point_on_line(
        a, b, c, current[0], current[1], thickness) else current_color
    )

