all:
	javac JavaSwing.java
	jar cvmf MANIFEST.MF JavaSwing.jar JavaSwing.class
	mkdir bin
	cat stub.sh JavaSwing.jar > bin/JavaSwing && chmod +x bin/JavaSwing_default
	rm JavaSwing.class
	rm JavaSwing.jar

clean:
	rm -rf bin
