all:
	mkdir bin
	gcc -Wall simple.c -o bin/xlib_default -lX11 -lXrandr
	gcc -Wall rects.c -o bin/xlib_rects -lX11 -lXrandr

clean:
	rm -rf bin
