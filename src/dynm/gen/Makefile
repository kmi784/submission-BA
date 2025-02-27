#********** Compiler command **********
FILE := main.cpp system.cpp
ARG := $(if $(ARG), $(ARG),1 0.31 0.61 0.01 F 100 100 5) 

FLAGS := -std=c++20 -O2 -Wall -Wpedantic -Wsign-conversion
COMPILER := g++ 




#********** Debugging configurations **********
debug: $(FILE) system.hpp
	$(COMPILER) $(FLAGS) $(FILE) -o debug
	time ./debug $(ARG)


#********** Release configurations **********
release:
	$(COMPILER) -std=c++20 -O2 $(FILE) -o $(DIR)


#********** Clean **********
clean:
	rm -rf debug L*
