all: aufgabe-3a aufgabe-3b aufgabe-3c

clean:
	rm -f aufgabe-3a aufgabe-3b aufgabe-3c

aufgabe-3a: aufgabe3a.cpp ggt.cpp ggt.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-3a aufgabe3a.cpp ggt.cpp

aufgabe-3b: aufgabe3b.cpp ggt.cpp ggt.hpp kgv.cpp kgv.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-3b aufgabe3b.cpp ggt.cpp kgv.cpp

aufgabe-3c: aufgabe3c.cpp dbe.cpp dbe.hpp ggt.cpp ggt.hpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-3c aufgabe3c.cpp dbe.cpp ggt.cpp

test: aufgabe-3c
	./aufgabe-3c 5.0 1.25 0.33 0.30 0.03 0.p33 0.3p30 -0.3p03 1.0p007 7.06p46341
