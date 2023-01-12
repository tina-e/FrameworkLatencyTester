#!/bin/sh

ITERATIONS=500

DATA_DIR="2023-01-12_pc-nocomp-2"
#killall -9 picom

#xfconf-query --channel=xfwm4 --property=/general/use_compositing --type=bool --set false

qdbus org.kde.KWin /Compositor suspend

sleep 5s
./start_measurement_new.sh gtk default $ITERATIONS $DATA_DIR
./start_measurement_new.sh JavaAWT default $ITERATIONS $DATA_DIR
./start_measurement_new.sh JavaSwing default $ITERATIONS $DATA_DIR
./start_measurement_new.sh pyqt6 default $ITERATIONS $DATA_DIR
./start_measurement_new.sh wxpython default $ITERATIONS $DATA_DIR

#./start_measurement_new.sh pyqt5 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pygame default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh tkinter default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengl $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 software $ITERATIONS $DATA_DIR

DATA_DIR="2023-01-12_pc-comp-2"

#xfconf-query --channel=xfwm4 --property=/general/use_compositing --type=bool --set true

qdbus org.kde.KWin /Compositor resume

sleep 5s
./start_measurement_new.sh gtk default $ITERATIONS $DATA_DIR
./start_measurement_new.sh JavaAWT default $ITERATIONS $DATA_DIR
./start_measurement_new.sh JavaSwing default $ITERATIONS $DATA_DIR
./start_measurement_new.sh pyqt6 default $ITERATIONS $DATA_DIR
./start_measurement_new.sh wxpython default $ITERATIONS $DATA_DIR

#./start_measurement_new.sh pyqt5 default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh pygame default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh tkinter default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengl $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
#./start_measurement_new.sh SDL2 software $ITERATIONS $DATA_DIR



#DATA_DIR="2022-12-02_laptop-picom"
#picom --config ~/.config/picom/picom.conf -b
#
#sleep 3s
#./start_measurement.sh pyqt5 default $ITERATIONS $DATA_DIR
#./start_measurement.sh pygame default $ITERATIONS $DATA_DIR
#./start_measurement.sh tkinter default $ITERATIONS $DATA_DIR
#./start_measurement.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
#./start_measurement.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
#./start_measurement.sh SDL2 opengl $ITERATIONS $DATA_DIR
#./start_measurement.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
#./start_measurement.sh SDL2 software $ITERATIONS $DATA_DIR
#
#DATA_DIR="2022-12-02_laptop-picom-nosync"
#killall -9 picom
#picom --config ~/.config/picom/picom_nosync.conf -b
#
#sleep 3s
#./start_measurement.sh pyqt5 default $ITERATIONS $DATA_DIR
#./start_measurement.sh pygame default $ITERATIONS $DATA_DIR
#./start_measurement.sh tkinter default $ITERATIONS $DATA_DIR
#./start_measurement.sh OPENGL_GLEW default $ITERATIONS $DATA_DIR
#./start_measurement.sh OPENGL_GLUT default $ITERATIONS $DATA_DIR
#./start_measurement.sh SDL2 opengl $ITERATIONS $DATA_DIR
#./start_measurement.sh SDL2 opengles2 $ITERATIONS $DATA_DIR
#./start_measurement.sh SDL2 software $ITERATIONS $DATA_DIR
#
#killall -9 picom
