all:
	mkdir bin
	g++ simple.cpp -lfltk -lXext -lX11 -lm -o bin/FLTK_default
	g++ rects.cpp -lfltk -lXext -lX11 -lm -o bin/FLTK_rects
	g++ image.cpp -lfltk -lfltk_images -lXext -lX11 -lm -o bin/FLTK_image
	#-lfltk_png -lfltk_z 

clean:
	rm -rf bin
