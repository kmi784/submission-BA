FILE ?= mean.cpp

D_TRGT := debug
R_TRGT := mean peak wham
BINARIES := ../../bin

CXX := g++
D_FLAGS := -std=c++20  -Wall -Wpedantic -Wsign-conversion -O0 -g
R_FLAGS := -std=c++20 -O2

ifeq ($(basename $(FILE)), mean)
    ARGS := ../../data/raw/equi/L30-U ./mean.txt 30
endif

ifeq ($(basename $(FILE)), peak)
    ARGS := ../../data/raw/equi/L30-U ./peak.txt 50 0.35 0.4 200
endif

ifeq ($(basename $(FILE)), wham)
    ARGS := ../../data/raw/equi/L30-U ./wham.txt 0.35 0.55 200
endif

all: $(D_TRGT) 

$(D_TRGT): $(FILE)
	$(CXX) $(D_FLAGS) $(FILE) -o debug
	@time ./$(D_TRGT) $(ARGS)

release:
	@for T in $(R_TRGT); do\
		$(CXX) $(R_FLAGS) $$T.cpp -o $(BINARIES)/$(basename $$T); \
	done

clean:
	rm -rf debug *.txt
