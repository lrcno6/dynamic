libdynamic.a:object.o primitive_data.o
	ar cr libdynamic.a object.o primitive_data.o
object.o:object.cpp object.h
	g++ -c object.cpp -Wall -g
primitive_data.o:primitive_data.cpp primitive_data.h object.h
	g++ -c primitive_data.cpp -Wall -g
release:
	g++ -c object.cpp primitive_data.cpp -O3
	ar cr libdynamic.a object.o primitive_data.o
clean:
	rm libdynamic.a object.o primitive_data.o