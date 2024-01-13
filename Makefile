allT : tests
	./tests -t

allM: Main
	./Main

test: test.cpp
	g++ -std=c++11 -Wall -c test.cpp

main: main.cpp coord.hpp animal.hpp population.hpp Grille.hpp Jeu.hpp
	g++ -std=c++11 -Wall -c main.cpp

coord: coord.cpp coord.hpp
	g++ -std=c++11 -Wall -c coord.cpp

animal: animal.cpp animal.hpp
	g++ -std=c++11 -Wall -c animal.cpp

population: population.cpp population.hpp
	g++ -std=c++11 -Wall -c population.cpp

grille: Grille.cpp Grille.hpp
	g++ -std=c++11 -Wall -c Grille.cpp

jeu: Jeu.cpp Jeu.hpp
	g++ -std=c++11 -Wall -c Jeu.cpp

tests: test.o coord.o animal.o population.o Grille.o Jeu.o
	g++ -o tests test.o coord.o animal.o population.o Grille.o Jeu.o
    
Main: main.o coord.o animal.o population.o Grille.o Jeu.o
	g++ -o Main main.o coord.o animal.o population.o Grille.o Jeu.o
