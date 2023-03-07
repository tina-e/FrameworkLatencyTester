simple:
	javac JavaSwing.java
	jar cvmf MANIFEST.MF JavaSwing.jar *.class
	mkdir -p bin
	cat stub.sh JavaSwing.jar > bin/JavaSwing_default && chmod +x bin/JavaSwing_default
	rm *.class
	rm JavaSwing.jar

rects:
	javac JavaSwing_rects.java
	jar cvmf MANIFEST_RECTS.MF JavaSwing_rects.jar *.class
	mkdir -p bin
	cat stub.sh JavaSwing_rects.jar > bin/JavaSwing_rects && chmod +x bin/JavaSwing_rects
	rm *.class
	rm JavaSwing_rects.jar

image:
	javac JavaSwing_image.java
	jar cvmf MANIFEST_IMAGE.MF JavaSwing_image.jar *.class
	mkdir -p bin
	cat stub.sh JavaSwing_image.jar > bin/JavaSwing_image && chmod +x bin/JavaSwing_image
	rm *.class
	rm JavaSwing_image.jar

all: simple rects image

clean:
	rm -rf bin
