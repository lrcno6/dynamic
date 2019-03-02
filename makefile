libdynamic.a:object.o
	ar cr libdynamic.a object.o
object.o:object.cpp object.h
	g++ -c object.cpp -g
clean:
	rm libdynamic.a object.o