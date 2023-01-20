sdl2:
	$(MAKE) -C SDL2/ all

glut:
	$(MAKE) -C OPENGL_GLUT/ all

glew:
	$(MAKE) -C OPENGL_GLEW/ all

gtk:
	$(MAKE) -C gtk/ all

swing:
	$(MAKE) -C JavaSwing/ all

java2d:
	$(MAKE) -C Java2D/ all

qt5:
	$(MAKE) -C Qt5/ all

Java2D:
	$(MAKE) -C Java2D/ all

FLTK:
	$(MAKE) -C FLTK/ all


all: glew glut sdl2 gtk swing qt5 java2d FLTK

clean:
	$(MAKE) -C SDL2/ clean
	$(MAKE) -C OPENGL_GLUT/ clean
	$(MAKE) -C OPENGL_GLEW/ clean
	$(MAKE) -C gtk/ clean
	$(MAKE) -C JavaSwing/ clean
	$(MAKE) -C Qt5/ clean
	$(MAKE) -C Java2D/ clean
	$(MAKE) -C FLTK/ clean
