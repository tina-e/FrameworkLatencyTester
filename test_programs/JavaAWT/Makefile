all:
	javac JavaAWT.java
	jar cvmf MANIFEST.MF JavaAWT.jar JavaAWT.class
	mkdir bin
	cat stub.sh JavaAWT.jar > bin/JavaAWT_default && chmod +x bin/JavaAWT_default
	rm JavaAWT.class
	rm JavaAWT.jar

clean:
	rm -rf bin
