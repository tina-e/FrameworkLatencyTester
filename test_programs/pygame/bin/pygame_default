#!/usr/bin/python3

import pygame
import sys
import time

(width, height) = (0,0)
running = True
screen = pygame.display.set_mode((width, height), pygame.FULLSCREEN)

background_color_black = (0,0,0)
background_color_white = (255,255,255)

screen.fill(background_color_black)

measure_counter = 0

pygame.display.flip()

while running:
    event = pygame.event.poll()
    if event.type == pygame.QUIT:
        running = False
    
    if event.type == pygame.MOUSEBUTTONDOWN:
        screen.fill(background_color_white)
    
    if event.type == pygame.MOUSEBUTTONUP:
        screen.fill(background_color_black)
        measure_counter+=1
    
    pygame.display.update()
