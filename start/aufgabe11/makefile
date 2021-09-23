all: example-1 example-2 example-3 aufgabe-11

clean:
	rm -f example-1 example-2 example-3 aufgabe-11

example-1: example_1.cpp canvas_window.cpp canvas_window.hpp canvas.hpp shape.hpp
	g++ -std=c++11 -ggdb -O0 example_1.cpp canvas_window.cpp -o example-1 -lX11

example-2: example_2.cpp canvas_window.cpp canvas_window.hpp canvas.hpp shape.hpp
	g++ -std=c++11 -ggdb -O0 example_2.cpp canvas_window.cpp -o example-2 -lX11

example-3: example_3.cpp canvas_window.cpp canvas_window.hpp canvas.hpp shape.hpp
	g++ -std=c++11 -ggdb -O0 example_3.cpp canvas_window.cpp -o example-3 -lX11

aufgabe-11: aufgabe11.cpp canvas_window.cpp canvas_window.hpp canvas.hpp shape.hpp
	g++ -std=c++11 -ggdb -O0 aufgabe11.cpp canvas_window.cpp -o aufgabe-11 -lX11
