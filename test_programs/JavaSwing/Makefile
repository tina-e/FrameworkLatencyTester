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

all: simple rects

clean:
	rm -rf bin
