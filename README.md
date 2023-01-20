# FrameworkLatencyTester

*Work in progress!*

This Repository contains:

 * a program to measure the latency of graphics frameworks (`latency_tester`)
 * a program that automatically triggers input events (`click_simulator`)
 * several test programs implemented with different frameworks (`test_programs`)
 * measurement data (`data`)

### Usage

 * make sure to start the program on the primary display!
 * build everything with `make` in the root directory
 * run `./start_measurement.sh PROGRAM_NAME NUM_ITERATIONS SUBDIRECTORY`
   * `PROGRAM_NAME` is the name of the program under test and should be equal to a subdirectory in *test_programs*. It is also the name of the log file that will be created.
   * `NUM_ITERATIONS` is the number of measurement iterations you want to make
   * `SUBDIRECTORY` is the name of a subdirectory in *data* which will be created and where the log file will be stored
 * in *start_measurement.sh*, you can also adjust delay times of the click simulator

## Framework List

This list is not complete.

### Low Level

 * OpenGL
 * Vulkan

### GUI Frameworks

 * Java Swing
 * Qt
 * PyQt
 * Tkinter
 * GTK
 * Cairo

### 2D Frameworks

 * SDL
 * SDL2
 * pygame
 * Pillow
 * OpenCV

### Game Engines

 * Unity
 * Unreal Engine
 * Irrlicht
 * OGRE
 * Panda3D

### Web

 * WebGL
 * HTML5 Canvas
 * plain JavaScript

## Required Packages

```
sudo apt install freeglut3-dev
sudo apt install libglew-dev
sudo apt install libgtk-3-dev
sudo apt install libcairo2-dev
sudo apt install default-jre default-jdk
sudo apt install libfltk1.3-dev libx11-dev libxext-dev
sudo apt install liballegro5-dev

pip3 install wxPython
pip3 install pyqt5
pip3 install pyqt6
pip3 install pygame
```
