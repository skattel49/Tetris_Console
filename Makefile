test: 
	g++ -o test main.cpp Board.cpp BRicky.cpp ORicky.cpp RZ.cpp CZ.cpp Smash.cpp Hero.cpp Teewee.cpp -lpthread
clean:
	rm -rf test