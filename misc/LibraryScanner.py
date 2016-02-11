#!/usr/bin/python
# Base code for a program that displays whether or not a student will be
# allowed into the library.
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

from Tkinter import *

class LibraryScanner():
  def __init__(self, window, text_entry):
    """
    Constructor for a LibraryScanner class. This should not be called unless
    unit testing.
    """
    self.window = window
    self.text_entry = text_entry
    self._bind_event_handlers()

  @staticmethod
  def create():
    """
    Factory method to create an instance of a LibraryScanner object.
    """
    window = Tk()
    window.geometry("400x400")
    label = Label(window, text='OSIS')
    label.place(x=100, y=205)
    text_entry = Entry(window, bd=5)
    text_entry.place(x=150, y=200)
    text_entry.configure(border=1)
    return LibraryScanner(window, text_entry)

  def _bind_event_handlers(self):
    if self.window:
      self.window.bind('<KeyPress>', self._onKeyPress)

  def _onKeyPress(self, event):
    """
    This is a callback function bound to the window's keypress event to
    handle a submission.
    """
    if event.char.isspace():
      self.text_entry.delete(0, len(self.text_entry.get()))

  def run(self):
    """
    Runs the LibraryScanner main loop.
    """
    self.window.mainloop()

if __name__ == '__main__':
  obj = LibraryScanner.create()
  obj.run()
