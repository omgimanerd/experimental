#!/usr/bin/python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)
# This is a class that contains utility methods for the Drawing class.

import math

class Util():
  @staticmethod
  def in_bound(x, lower, upper):
    if lower > upper:
      tmp = lower
      lower = upper
      upper = tmp
    return x >= lower and x <= upper

  @staticmethod
  def is_point_on_line(a, b, c, px, py, threshold=2):
    return (abs(px * a + py * b + c) / math.sqrt(a * a + b * b)) <= threshold

  @staticmethod
  def is_point_on_circle(cx, cy, r, px, py, threshold=2):
    return get_euclidean_distance(cx, cy, px, py) - r <= threshold

  @staticmethod
  def get_manhattan_distance(x1, y1, x2, y2):
    return abs(y2 - y1) + abs(x2 - x1)

  @staticmethod
  def get_euclidean_distance_sq(x1, y1, x2, y2):
    return ((x2 - x1) ** 2) + ((y2 - y1) ** 2)

  @staticmethod
  def get_euclidean_distance(x1, y1, x2, y2):
    return math.sqrt(get_euclidean_distance_sq(x1, y1, x2, y1))

  @staticmethod
  def are_points_closer_than(x1, y1, x2, y2, d):
    return get_euclidean_distance_sq(x1, y1, x2, y2) <= d ** 2
