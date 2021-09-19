all: keycodes example-1 example-2 pong-classic pong-power

clean:
	rm -f keycodes example-1 example-2 pong-classic pong-power

keycodes: keycodes.cpp
	g++ -std=c++11 -ggdb -O0 keycodes.cpp -o keycodes -lX11

example-1: example_1.cpp render_window.cpp render_window.hpp
	g++ -std=c++11 -ggdb -O0 example_1.cpp render_window.cpp -o example-1 -lX11

example-2: example_2.cpp render_window.cpp render_window.hpp
	g++ -std=c++11 -ggdb -O0 example_2.cpp render_window.cpp -o example-2 -lX11

pong-classic: pong_classic.cpp render_window.cpp render_window.hpp
	g++ -std=c++11 -ggdb -O0 pong_classic.cpp render_window.cpp -o pong-classic -lX11

pong-power: pong_power.cpp render_window.cpp render_window.hpp
	g++ -std=c++11 -ggdb -O0 pong_power.cpp render_window.cpp -o pong-power -lX11
