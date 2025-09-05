FILE := main.cpp system.cpp
FLAGS := -std=c++20 -O2 
ARG := $(if $(ARG), $(ARG),1 0.31 0.61 0.01 F 100 100 5) 

debug: $(FILE) system.hpp
	g++ $(FLAGS) -Wall -Wpedantic -Wsign-conversion $(FILE) -o debug
	time ./debug $(ARG)

release:
	g++ $(FILE) -o ../../../bin/dynm-$(L)-$(ALGORITHM)

clean:
	rm -rf debug L*
