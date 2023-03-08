all:
	mkdir bin
	gcc -Wall simple.c -o bin/xcb_default -lxcb
	gcc -Wall rects.c -o bin/xcb_rects -lxcb
	gcc -Wall image.c -o bin/xcb_image -lxcb -lpng -lxcb-image

clean:
	rm -rf bin
