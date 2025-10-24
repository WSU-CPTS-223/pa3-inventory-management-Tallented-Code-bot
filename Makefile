out: clean compile execute

compile: main.cpp
	g++ -g -Wall -std=c++14 main.cpp -o main

execute: main
	./main

clean:
	rm -f main
