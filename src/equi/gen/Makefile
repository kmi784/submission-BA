FILE := main.cpp system.cpp
FLAGS := -std=c++20 -O2 
ARG := $(if $(ARG), $(ARG),1 0.4 U 2000 2000 2000)

debug: $(FILE) system.hpp
	g++ $(FLAGS) -Wall -Wpedantic -Wsign-conversion $(FILE) -o debug
	time ./debug $(ARG)

release:
	g++ $(FLAGS) $(FILE) -o ../../../bin/equi-$(L)-$(ALGORITHM)

clean:
	rm -rf debug L*
