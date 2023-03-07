#!/usr/bin/python3

import pyglet
from pyglet.shapes import Rectangle
from pyglet import app
from pyglet.window import Window

# Define the width and height of the window
WINDOW_WIDTH = 1920
WINDOW_HEIGHT = 1080

# Create a Pyglet window
win = Window(fullscreen=True)

rect = Rectangle(x=0, y=0, width=WINDOW_WIDTH, height=WINDOW_HEIGHT, color=(0, 0, 0))

img = pyglet.image.load('noise.png')

pressed = False

@win.event
def on_mouse_press(x, y, button, modifiers):
    global pressed
    pressed = True

@win.event
def on_mouse_release(x, y, button, modifiers):
    global pressed
    pressed = False

# Define a function to draw the rectangle
@win.event
def on_draw():
    win.clear()
    if pressed:
        img.blit(0, 0, 0)
    else:
        rect.draw()

app.run()
