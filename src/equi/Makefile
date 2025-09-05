FILE := mean.cpp
FLAGS := -std=c++20 -O2

ARG := ../../data/raw/equi/L30-U ./mean.txt 30 
#ARG := ../../data/raw/equi/L30-U ./peak.txt 50 0.35 0.4 200
#ARG := ../../data/raw/equi/L30-U ./wham.txt 0.35 0.55 200

debug: $(FILE) 
	g++ $(FLAGS) -Wall -Wpedantic -Wsign-conversion $(FILE) -o debug
	time ./debug $(ARG)

release:
	g++ $(FLAGS) $(FILE) -o ../../bin/$(basename $(FILE))

clean:
	rm -rf debug *.txt
