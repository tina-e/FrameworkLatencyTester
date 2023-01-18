all:
	mkdir bin
	g++ simple.cpp -lGL -lGLEW -lSDL2 -o bin/OPENGL_GLEW_default
	g++ simple.cpp -lGL -lGLEW -lSDL2 -DDOUBLEBUF -o bin/OPENGL_GLEW_double

clean:
	rm -rf bin
