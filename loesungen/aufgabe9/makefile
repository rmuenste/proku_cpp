all: aufgabe-9

clean:
	rm -f aufgabe-9 minerva1.jpg minerva2.jpg bahn1.jpg bahn2.jpg royo1.jpg royo2.jpg

aufgabe-9: aufgabe9.cpp image.cpp image.hpp jpeg_io.cpp jpeg_io.hpp
	g++ -std=c++11 -ggdb -Wall -O0 -o aufgabe-9 aufgabe9.cpp image.cpp jpeg_io.cpp -ljpeg

bilder: aufgabe-9
	./aufgabe-9 bilder/minerva.jpg minerva1.jpg minerva2.jpg
	./aufgabe-9 bilder/bahn.jpg bahn1.jpg bahn2.jpg
	./aufgabe-9 bilder/royo.jpg royo1.jpg royo2.jpg
