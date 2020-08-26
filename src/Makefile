planet: main.o uci.o board.o move.o
	g++ main.o uci.o board.o move.o -o planet -std=c++17

main.o: main.cpp
	g++ -c -g main.cpp -std=c++17

uci.o: uci.cpp uci.hpp
	g++ -c -g uci.cpp -std=c++17

board.o: board.cpp board.hpp
	g++ -c -g board.cpp -std=c++17

move.o: move.cpp move.hpp
	g++ -c -g move.cpp -std=c++17

clean:
	del *.o