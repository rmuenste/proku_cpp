all: aufgabe-6

clean:
	rm -f aufgabe-6 image1.jpg image2.jpg image3.jpg image4.jpg image5.jpg

# Ziel fuer Aufgabe 6)
aufgabe-6: aufgabe6.cpp parse.cpp parse.hpp jpeg_io.cpp jpeg_io.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-6 aufgabe6.cpp parse.cpp jpeg_io.cpp -ljpeg

# Lasse die drei Bilder rendern
images: aufgabe-6
	./aufgabe-6 image1.jpg 1280 960 1.6 1.2  0.41  0.14 100 100
	./aufgabe-6 image2.jpg 1280 960 1.6 1.2 -0.60  0.50 100 100
	./aufgabe-6 image3.jpg 1280 960 1.6 1.2 -0.78  0.13 100 100
	./aufgabe-6 image4.jpg 1280 960 1.6 1.2  0.00 -0.80 100 100
	./aufgabe-6 image5.jpg 1280 960 0.4 0.3 -1.40  0.00 100 100
