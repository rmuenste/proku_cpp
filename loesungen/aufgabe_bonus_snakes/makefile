all: example-1 example-2 example-3 snakes-game

clean:
	rm -f example-1 example-2 example-3 snakes-game

example-1: example1.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp
	g++ -std=c++11 -Wall -ggdb -O0 -o example-1 example1.cpp console.cpp timer.cpp -lncurses -ltinfo

example-2: example2.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp
	g++ -std=c++11 -Wall -ggdb -O0 -o example-2 example2.cpp console.cpp timer.cpp -lncurses -ltinfo

example-3: example3.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp
	g++ -std=c++11 -Wall -ggdb -O0 -o example-3 example3.cpp console.cpp timer.cpp -lncurses -ltinfo

snakes-game: snakes_game.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp snake.cpp
	g++ -std=c++11 -Wall -ggdb -O0 -o snakes-game snakes_game.cpp snake.cpp console.cpp timer.cpp -lncurses -ltinfo

###############################################################################################################

snakes-demo: snakes-phase-1 snakes-phase-2 snakes-phase-3

snakes-phase-1: snakes_phase_1.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp snake.cpp
	g++ -std=c++11 -Wall -O3 -o snakes-phase-1 snakes_phase_1.cpp snake.cpp console.cpp timer.cpp -lncurses -ltinfo

snakes-phase-2: snakes_phase_2.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp snake.cpp
	g++ -std=c++11 -Wall -O3 -o snakes-phase-2 snakes_phase_2.cpp snake.cpp console.cpp timer.cpp -lncurses -ltinfo

snakes-phase-3: snakes_phase_3.cpp base.hpp console.hpp console.cpp timer.hpp timer.cpp snake.cpp
	g++ -std=c++11 -Wall -O3 -o snakes-phase-3 snakes_phase_3.cpp snake.cpp console.cpp timer.cpp -lncurses -ltinfo
