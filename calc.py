#!/usr/bin/python

from numpy import arange, linspace

def delta_x(a, b, n):
    return (b - a) / n

def left_riemann_sum(f, a, b, n):
    return delta_x(a, b, n) * sum(
        [f(x) for x in linspace(a, b, n + 1, endpoint=False)])

def right_riemann_sum(f, a, b, n):
    return delta_x(a, b, n) * sum(
        [f(x) for x in linspace(a, b, n + 1)[1:]])

def midpoint_approximation(f, a, b, n):
    delta = delta_x(a, b, n)
    return delta * sum(
        [f(x) for x in arange(a + (delta / 2), b, delta)])

def trapezoidal_approximation(f, a, b, n):
    return (left_riemann_sum(f, a, b, n) + right_riemann_sum(f, a, b, n)) / 2

def simpsons_rule_approximation(f, a, b, n):
    series = linspace(a, b, n + 1)
    for index, term in enumerate(series):
        if index == 0 or index == len(series) - 1:
            series[index] = f(term)
        elif not(index % 2): # even
            series[index] = 2 * f(term)
        else:
            series[index] = 4 * f(term)
    return (delta_x(a, b, n) / 3) * sum(series)

if __name__ == '__main__':
    from math import *
    exec("f = lambda x: {}".format(input("Input your function: lambda x: ")))
    a = int(input("Lower limit: "))
    b = int(input("Upper limit: "))
    n = int(input("n: "))
    print("-----")
    print("Left Riemann Sum Approximation: {}".format(
        left_riemann_sum(f, a, b, n)))
    print("Right Riemann Sum Approximation: {}".format(
        right_riemann_sum(f, a, b, n)))
    print("Midpoint Sum Approximation: {}".format(
        midpoint_approximation(f, a, b, n)))
    print("Trapezoidal Sum Approximation: {}".format(
        trapezoidal_approximation(f, a, b, n)))
    print("Simpson's Rule Approximation: {}".format(
        simpsons_rule_approximation(f, a, b, n)))
