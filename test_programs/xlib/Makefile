all:
	mkdir bin
	gcc -Wall simple.c -o bin/xlib_default -lX11 -lXrandr
	gcc -Wall rects.c -o bin/xlib_rects -lX11 -lXrandr
	gcc -Wall image.c -o bin/xlib_image -lX11 -lXrandr -lpng

clean:
	rm -rf bin
