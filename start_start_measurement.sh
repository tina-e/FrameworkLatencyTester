#!/bin/sh

DATA_DIR="2022-11-17_laptop-picom"
ITERATIONS=100

sleep 5s
./start_measurement.sh pyqt5 default $ITERATIONS $DATA_DIR
./start_measurement.sh pygame default $ITERATIONS $DATA_DIR
./start_measurement.sh tkinter default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengl $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 software $ITERATIONS $DATA_DIR
