
#********** Compiler command **********
FILE := $(if $(FILE), $(FILE), peak.cpp)
ARG := $(if $(ARG), $(ARG), ../../data/kalz/L30-U ./peak.txt 50 0.35 0.4 200)

FLAGS := -std=c++20 -Wall -Wpedantic -Wsign-conversion 
COMPILER := g++ 



#********** Debugging configurations **********
debug: $(FILE) 
	$(COMPILER) $(FLAGS) $(FILE) -o debug
	time ./debug $(ARG)


#********** Release configurations **********
release:
	$(COMPILER) -std=c++20 -O2 $(FILE) -o $(DIR)


#********** Clean **********
clean:
	rm -rf debug *.txt
