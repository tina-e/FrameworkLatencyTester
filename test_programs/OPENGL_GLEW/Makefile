all:
	mkdir bin
	g++ simple.cpp -lGL -lGLEW -lSDL2 -o bin/OPENGL_GLEW_default

clean:
	rm -rf bin

dev:
	make clean
	make
	./bin/OPENGL_GLEW_default