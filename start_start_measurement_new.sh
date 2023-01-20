#!/bin/sh

ITERATIONS=500

DATA_DIR="2023-01-19_pc-nocomp-xfce"
#killall -9 picom

xfconf-query --channel=xfwm4 --property=/general/use_compositing --type=bool --set false

#qdbus org.kde.KWin /Compositor suspend

sleep 5s

./start_measurement_new.sh FLTK default $ITERATIONS $DATA_DIR
./start_measurement_new.sh FLTK rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh gtk rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh OPENGL_GLUT rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh pygame rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh pyqt5 rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh SDL2 rects_opengl $ITERATIONS $DATA_DIR
./start_measurement_new.sh SDL2 rects_opengles2 $ITERATIONS $DATA_DIR
./start_measurement_new.sh SDL2 rects_software $ITERATIONS $DATA_DIR
./start_measurement_new.sh tkinter rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh Java2D rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh JavaSwing rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh OPENGL_GLEW rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh pyqt6 rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh Qt5 rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh wxpython rects $ITERATIONS $DATA_DIR

#./start_measurement_new.sh gtk default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh Java2D default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh JavaSwing default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pyqt6 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh wxpython default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh Qt5 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pyqt5 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pygame default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengl $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 software $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 rects_opengl $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 rects_opengles2 $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 rects_software $ITERATIONS $DATA_DIR
#./start_measurement_new.sh allegro default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh tkinter default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLEW double $ITERATIONS $DATA_DIR


DATA_DIR="2023-01-19_pc-comp-xfce"

xfconf-query --channel=xfwm4 --property=/general/use_compositing --type=bool --set true

#qdbus org.kde.KWin /Compositor resume
#
sleep 5s

./start_measurement_new.sh FLTK default $ITERATIONS $DATA_DIR
./start_measurement_new.sh FLTK rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh gtk rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh OPENGL_GLUT rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh pygame rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh pyqt5 rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh SDL2 rects_opengl $ITERATIONS $DATA_DIR
./start_measurement_new.sh SDL2 rects_opengles2 $ITERATIONS $DATA_DIR
./start_measurement_new.sh SDL2 rects_software $ITERATIONS $DATA_DIR
./start_measurement_new.sh tkinter rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh Java2D rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh JavaSwing rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh OPENGL_GLEW rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh pyqt6 rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh Qt5 rects $ITERATIONS $DATA_DIR
./start_measurement_new.sh wxpython rects $ITERATIONS $DATA_DIR



#./start_measurement_new.sh gtk default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh Java2D default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh JavaSwing default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pyqt6 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh wxpython default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh allegro default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh Qt5 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pyqt5 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pygame default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh tkinter default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengl $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 software $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 rects_opengl $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 rects_opengles2 $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 rects_software $ITERATIONS $DATA_DIR
