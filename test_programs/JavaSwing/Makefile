all:
	javac JavaSwing.java
	jar cvmf MANIFEST.MF JavaSwing.jar *.class
	mkdir bin
	cat stub.sh JavaSwing.jar > bin/JavaSwing_default && chmod +x bin/JavaSwing_default
	rm *.class
	rm JavaSwing.jar

clean:
	rm -rf bin
