all: aufgabe-8

clean:
	rm -f aufgabe-8

aufgabe-8: aufgabe8.cpp
	g++ -std=c++11 -Wall -ggdb -O0 -o aufgabe-8 aufgabe8.cpp

valgrind-test: aufgabe-8
	valgrind -v --leak-check=full ./aufgabe-8 < script.txt
