SRC := main.cpp system.cpp
HDR := system.hpp

D_TRGT := debug
TRGT := egen

TESTS := ../../tests

CXX := g++
D_FLAGS := -std=c++20  -Wall -Wpedantic -Wsign-conversion -O0 -g
R_FLAGS := -std=c++20 -O2
ARGS := 1 0.4 U 2000 2000 2000

# build
all: $(D_TRGT)

$(D_TRGT): $(SRC) $(HDR)
	$(CXX) $(D_FLAGS) $(SRC) -o $(D_TRGT)
	@echo "Running debug build..."
	@time ./$(D_TRGT) $(ARGS)
	$(MAKE) test

release: 
	$(CXX) $(R_FLAGS) $(SRC) -o ../../../bin/$(TRGT)-$(L)-$(ALGORITHM)

# test
test: test-run test-diff
	@echo "Test passed."

test-run:
	@echo "Collecting program output..."
	@rm -rf $(TESTS)/current
	@mkdir -p $(TESTS)/current
	@mv L*-*/ $(TESTS)/current/

test-diff:
	@diff -r $(TESTS)/ref-$(TRGT) $(TESTS)/current

# clean up
clean:
	@rm -rf debug $(TESTS)/current

.PHONY: release clean test test-run test-diff
