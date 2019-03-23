libdynamic.a:object.o
	ar cr libdynamic.a object.o
object.o:object.cpp object.h
	g++ -c object.cpp -Wall -g
release:
	g++ -c object.cpp -O3
	ar cr libdynamic.a object.o
clean:
	rm libdynamic.a object.o