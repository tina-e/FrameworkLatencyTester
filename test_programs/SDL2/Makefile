all:
	mkdir bin
	g++ simple.cpp -lSDL2main -lSDL2 -DDRIVER='"opengl"' -o bin/SDL2_opengl
	g++ simple.cpp -lSDL2main -lSDL2 -DDRIVER='"opengles2"' -o bin/SDL2_opengles2
	g++ simple.cpp -lSDL2main -lSDL2 -DDRIVER='"software"' -o bin/SDL2_software
	g++ rects.cpp -lSDL2main -lSDL2 -DDRIVER='"opengl"' -o bin/SDL2_rects_opengl
	g++ rects.cpp -lSDL2main -lSDL2 -DDRIVER='"opengles2"' -o bin/SDL2_rects_opengles2
	g++ rects.cpp -lSDL2main -lSDL2 -DDRIVER='"software"' -o bin/SDL2_rects_software

clean:
	rm -rf bin
