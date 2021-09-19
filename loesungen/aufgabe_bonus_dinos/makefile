all: aufgabe-9a aufgabe-9b aufgabe-9c aufgabe-9d aufgabe-9e

clean:
	rm -f aufgabe-9a aufgabe-9b aufgabe-9c aufgabe-9d aufgabe-9e
	rm -f ./images/*.jpg
	rm -f ./output_9c/*.jpg
	rm -f ./output_9d/*.jpg

aufgabe-9a: aufgabe9a.cpp test_helpers.hpp point.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-9a aufgabe9a.cpp

aufgabe-9b: aufgabe9b.cpp test_helpers.hpp point.hpp triangle.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-9b aufgabe9b.cpp

aufgabe-9c: aufgabe9c.cpp test_helpers.hpp point.hpp triangle.hpp frame.hpp jpeg_io.cpp jpeg_io.hpp camera.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-9c aufgabe9c.cpp jpeg_io.cpp -ljpeg

aufgabe-9d: aufgabe9d.cpp test_helpers.hpp point.hpp triangle.hpp frame.hpp jpeg_io.cpp jpeg_io.hpp camera.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-9d aufgabe9d.cpp jpeg_io.cpp -ljpeg

aufgabe-9e: aufgabe9e.cpp point.hpp triangle.hpp frame.hpp jpeg_io.cpp jpeg_io.hpp camera.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-9e aufgabe9e.cpp jpeg_io.cpp -ljpeg

test: aufgabe-9a aufgabe-9b aufgabe-9c
	./aufgabe-9a
	./aufgabe-9b
	./aufgabe-9c
	./aufgabe-9d

#         Parameter: name    width height dist  yaw pitch roll c_x  c_y  c_z
me-happy: aufgabe-9e
	./aufgabe-9e acrocan  1280    720    4  0.8  -0.2    0   0  2.5  3.0
	./aufgabe-9e brachio  1280    720    6  2.0   0.2    0   0  4.0 -5.0
	./aufgabe-9e camara   1280    720    7  1.0  -0.3    0  -3  2.7  2.0
	./aufgabe-9e trice    1280    720  4.7  0.9  -0.1    0   0  2.2  2.0
