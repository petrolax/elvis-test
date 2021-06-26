all:
	g++ src/main.cpp src/datafile.cpp -o bin/main -std=c++11 -pthread -lboost_system -lboost_filesystem