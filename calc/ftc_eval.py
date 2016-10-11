#!/usr/bin/python

if __name__ == '__main__':
    from math import *
    exec("f = lambda x: {}".format(input("Input your function: lambda x: ")))
    a = int(input("Lower limit: "))
    b = int(input("Upper limit: "))
    print("Result: {}".format(f(b) - f(a)))
