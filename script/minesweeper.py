#!/usr/bin/python
# Minesweeper in Python
# Author: Alvin Lin (alvin.lin.dev@gmail.com)

from Tkinter import *

import random

BUTTON_WIDTH = 36
BUTTON_HEIGHT = 29

class MineSweeper():

    def __init__(self, rows, cols, root, buttons, textvariables, grid,
                 resetButton, master=None):
        self.rows = rows
        self.cols = cols
        self.root = root
        self.buttons = buttons
        self.textvariables = textvariables
        self.grid = grid
        self.resetButton = resetButton

    @staticmethod
    def create(rows, cols):
        root = Tk()
        width = (rows * BUTTON_WIDTH)
        height = (cols * BUTTON_HEIGHT) + 40
        root.geometry("%dx%d" % (width, height))
        textvariables = [[StringVar() for y in range(rows)] for x in range(cols)]
        buttons = [[Button(root, width=1, height=1,
                           textvariable=textvariables[x][y]) for y in range(
                               rows)] for x in range(cols)]
        grid = [[-1 for y in range(rows)] for x in range(cols)]

        resetButton = Button(root, text="Reset")

        m = MineSweeper(rows, cols, root, buttons, textvariables, grid,
                        resetButton)
        m._reset()
        m._setup_buttons()
        return m

    def _reset(self):
        num_mines = int(self.rows * self.cols * 0.15)
        self.grid = [[-1 for y in range(self.rows)] for x in range(self.cols)]
        for i in range(num_mines):
            x = random.randint(0, self.cols - 1)
            y = random.randint(0, self.rows - 1)
            while self.grid[x][y] == "M":
                x = random.randint(0, self.cols - 1)
                y = random.randint(0, self.rows - 1)
            self.grid[x][y] = "M"
        for x in range(self.cols):
            for y in range(self.rows):
                self.textvariables[x][y].set("")

    def _setup_buttons(self):
        self.resetButton.grid(row=self.cols+1, columnspan=self.cols)
        self.resetButton.config(command=self._reset)
        for x in range(self.cols):
            for y in range(self.rows):
                # We reverse this because Python list of lists are weird and
                # x goes down the list (y on the screen).
                self.buttons[x][y].grid(column=y, row=x)
                self.buttons[x][y].config(command=self._get_callback(x, y))

    def _get_callback(self, x, y):
        def fn():
            if self.grid[x][y] == "M":
                for i in range(100):
                    print "You lost!"
            else:
                self._propagate_click(x, y)
                for i in range(self.cols):
                    for j in range(self.rows):
                        if self.grid[i][j] != -1 and self.grid[i][j] != "M":
                            self.textvariables[i][j].set("%s" % self.grid[i][j])
        return fn

    def _propagate_click(self, x, y):
        if self.grid[x][y] != -1:
            return None
        mines = self._get_mines(x, y)
        self.grid[x][y] = mines
        if mines == 0:
            if self._in_range(x, y - 1):
                self._propagate_click(x, y - 1)
            if self._in_range(x + 1, y):
                self._propagate_click(x + 1, y)
            if self._in_range(x, y + 1):
                self._propagate_click(x, y + 1)
            if self._in_range(x - 1, y):
                self._propagate_click(x - 1, y)

    def _get_mines(self, x, y):
        mines = 0
        x_offset = [-1,  0,  1, 1, 1, 0, -1, -1]
        y_offset = [-1, -1, -1, 0, 1, 1,  1,  0]
        for offset in zip(x_offset, y_offset):
            if self._in_range(x + offset[0], y + offset[1]):
                if self.grid[x + offset[0]][y + offset[1]] == "M":
                    mines += 1
        return mines
        
    def _in_range(self, x, y):
        return x < self.cols and x >= 0 and y < self.rows and y >= 0
    
    def run(self):
        self.root.mainloop()

if __name__ == '__main__':
    app = MineSweeper.create(10, 15)
    app.run()

