all:
	javac Java2D.java
	jar cvmf MANIFEST.MF Java2D.jar *.class
	mkdir bin
	cat stub.sh Java2D.jar > bin/Java2D_default && chmod +x bin/Java2D_default
	rm *.class
	rm Java2D.jar

clean:
	rm -rf bin
