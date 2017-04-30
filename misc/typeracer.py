#!/usr/bin/python3

"""
var out = function(id1, id2) {
  var fword = "";
  var text = "";
  for (var i = 0; i < 9999; ++i) {
    try {
      fword = $(`#nhwMiddlegwt-uid-${i}`).innerHTML.trim();
    } catch(e) {}
    try {
      text = $(`#nhwRightgwt-uid-${i}`).innerHTML.trim();
    } catch(e) {}
    if (fword && text) {
      break;
    }
  }
  console.log(fword + " " + text);
};
"""

import pyautogui
import time

print("Enter words:")
words = input()

time.sleep(2)
pyautogui.typewrite(words, interval=0.03);
