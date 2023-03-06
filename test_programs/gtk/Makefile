all:
	mkdir bin
	gcc simple.c -o bin/gtk_default  `pkg-config --cflags --libs gtk+-3.0` 
	gcc rects.c -o bin/gtk_rects  `pkg-config --cflags --libs gtk+-3.0` 
	gcc image.c -o bin/gtk_image  `pkg-config --cflags --libs gtk+-3.0` 

clean:
	rm -rf bin
