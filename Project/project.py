#!/usr/bin/env python3
# Author: Alvin Lin (axl1439)
# Author: Stefan Aleksic

import matplotlib.pyplot as plt
import numpy as np

import re

FILENAME = 'ZI8D_JUM_2018_08_13_1930_Circumnavigate_RIT_with_Squiggles.txt'

TIME = 0
LATITUDE = 1
LONGITUDE = 2
SPEED = 3
TRACKING_ANGLE = 4
FIX = 5
SATELLITES = 6
DILUTION_OF_PRECISION = 7
ALTITUDE = 8

def parseLatitude(direction, value):
    matches = re.search('([0-9]{2})([0-9]{2}.[0-9]+)', value)
    degrees = float(matches.group(1))
    minutes = float(matches.group(2)) / 60
    return (-1 if direction == 'S' else 1) * (degrees + minutes)

def parseLongitude(direction, value):
    matches = re.search('([0-9]{3})([0-9]{2}.[0-9]+)', value)
    degrees = float(matches.group(1))
    minutes = float(matches.group(2)) / 60
    return (-1 if direction == 'W' else 1) * (degrees + minutes)

def preprocess_data_row(row):
    print(row)
    row = row.strip().split(',')
    if row[0] == '$GPRMC':
        return [
            float(row[1]),                  # TIME
            parseLatitude(row[4], row[3]),  # LATITUDE
            parseLongitude(row[6], row[5]), # LONGITUDE
            float(row[7]),                  # SPEED
            float(row[8]),                  # TRACKING_ANGLE
            -1,                             # FIX
            -1,                             # SATELLITES
            -1,                             # DILUTION_OF_PRECISION
            -1                              # ALTITUDE
        ]
    elif row[0] == '$GPGGA':
        return [
            float(row[1]),                  # TIME
            parseLatitude(row[3], row[2]),  # LATITUDE
            parseLongitude(row[5], row[4]), # LONGITUDE
            -1,                             # SPEED
            -1,                             # TRACKING_ANGLE
            float(row[6]),                  # FIX
            float(row[7]),                  # SATELLITES
            float(row[8]),                  # DILUTION_OF_PRECISION
            float(row[9])                   # ALTITUDE
        ]
    else:
        raise TypeError('Unknown data row encountered')

def is_valid_row(row):
    return row.startswith('$GP')

def get_data():
    with open(FILENAME) as f:
        return np.array(
            [preprocess_data_row(row) for row in f if is_valid_row(row)])

def main():
    data = get_data()
    print(data[:10])

if __name__ == '__main__':
    main()
