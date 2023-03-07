all:
	mkdir bin
	g++ simple.cpp -lSDL2main -lSDL2 -DDRIVER='"opengl"' -o bin/SDL2_opengl
	g++ simple.cpp -lSDL2main -lSDL2 -DDRIVER='"opengles2"' -o bin/SDL2_opengles2
	g++ simple.cpp -lSDL2main -lSDL2 -DDRIVER='"software"' -o bin/SDL2_software
	g++ rects.cpp -lSDL2main -lSDL2 -DDRIVER='"opengl"' -o bin/SDL2_rects_opengl
	g++ rects.cpp -lSDL2main -lSDL2 -DDRIVER='"opengles2"' -o bin/SDL2_rects_opengles2
	g++ rects.cpp -lSDL2main -lSDL2 -DDRIVER='"software"' -o bin/SDL2_rects_software
	g++ image.cpp -lSDL2main -lSDL2 -lSDL2_image -DDRIVER='"opengl"' -o bin/SDL2_image_opengl
	g++ image.cpp -lSDL2main -lSDL2 -lSDL2_image -DDRIVER='"opengles2"' -o bin/SDL2_image_opengles2
	g++ image.cpp -lSDL2main -lSDL2 -lSDL2_image -DDRIVER='"software"' -o bin/SDL2_image_software

clean:
	rm -rf bin
