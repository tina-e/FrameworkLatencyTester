simple:
	javac Java2D.java
	jar cvmf MANIFEST.MF Java2D.jar *.class
	mkdir -p bin
	cat stub.sh Java2D.jar > bin/Java2D_default && chmod +x bin/Java2D_default
	rm *.class
	rm Java2D.jar

rects:
	javac Java2D_rects.java
	jar cvmf MANIFEST_RECTS.MF Java2D_rects.jar *.class
	mkdir -p bin
	cat stub.sh Java2D_rects.jar > bin/Java2D_rects && chmod +x bin/Java2D_rects
	rm *.class
	rm Java2D_rects.jar

all: simple rects

clean:
	rm -rf bin
