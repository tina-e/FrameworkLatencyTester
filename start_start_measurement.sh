#!/bin/sh

sleep 5s
./start_measurement.sh pyqt5 default 100 test_compositor
./start_measurement.sh pygame default 100 test_compositor
#./start_measurement.sh tkinter default 100 test_compositor
./start_measurement.sh OPENGL_GLEW default 100 test_compositor
#./start_measurement.sh OPENGL_GLUT default 100 test_compositor
#./start_measurement.sh SDL2 opengl 100 test_compositor
#./start_measurement.sh SDL2 opengles2 100 test_compositor
#./start_measurement.sh SDL2 software 100 test_compositor
