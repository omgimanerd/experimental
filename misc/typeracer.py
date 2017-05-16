#!/usr/bin/python3

"""
$('.nonHideableWords').children[1].innerHTML +
$('.nonHideableWords').children[3].innerHTML
"""

import pyautogui
import time

print("Enter words:")
words = input()

time.sleep(2)
pyautogui.typewrite(words, interval=0.05);
