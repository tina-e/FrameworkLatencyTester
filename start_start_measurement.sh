#!/bin/sh

ITERATIONS=100

DATA_DIR="2022-12-02_laptop"
killall -9 picom

sleep 3s
./start_measurement.sh pyqt5 default $ITERATIONS $DATA_DIR
./start_measurement.sh pygame default $ITERATIONS $DATA_DIR
./start_measurement.sh tkinter default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengl $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 software $ITERATIONS $DATA_DIR

DATA_DIR="2022-12-02_laptop-picom"
picom --config ~/.config/picom/picom.conf -b

sleep 3s
./start_measurement.sh pyqt5 default $ITERATIONS $DATA_DIR
./start_measurement.sh pygame default $ITERATIONS $DATA_DIR
./start_measurement.sh tkinter default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengl $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 software $ITERATIONS $DATA_DIR

DATA_DIR="2022-12-02_laptop-picom-nosync"
killall -9 picom
picom --config ~/.config/picom/picom_nosync.conf -b

sleep 3s
./start_measurement.sh pyqt5 default $ITERATIONS $DATA_DIR
./start_measurement.sh pygame default $ITERATIONS $DATA_DIR
./start_measurement.sh tkinter default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
./start_measurement.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengl $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
./start_measurement.sh SDL2 software $ITERATIONS $DATA_DIR

killall -9 picom
