sdl2:
	$(MAKE) -C SDL2/ all

glut:
	$(MAKE) -C OPENGL_GLUT/ all

glew:
	$(MAKE) -C OPENGL_GLEW/ all

gtk:
	$(MAKE) -C gtk/ all

awt:
	$(MAKE) -C JavaAWT/ all

swing:
	$(MAKE) -C JavaSwing/ all

java2d:
	$(MAKE) -C Java2D/ all

qt5:
	$(MAKE) -C Qt5/ all

allegro:
	$(MAKE) -C allegro/ all

all: glew glut sdl2 gtk awt swing qt5 allegro java2d

clean:
	$(MAKE) -C SDL2/ clean
	$(MAKE) -C OPENGL_GLUT/ clean
	$(MAKE) -C OPENGL_GLEW/ clean
	$(MAKE) -C gtk/ clean
	$(MAKE) -C JavaAWT/ clean
	$(MAKE) -C JavaSwing/ clean
	$(MAKE) -C Qt5/ clean
	$(MAKE) -C allegro/ clean
	$(MAKE) -C java2d/ clean
