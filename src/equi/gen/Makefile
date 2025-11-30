SRC := main.cpp system.cpp
HDR := system.hpp

D_TRGT := debug
TRGT := egen

TESTS := ../../helper
BINARIES := ../../../bin

CXX := g++
D_FLAGS := -std=c++20  -Wall -Wpedantic -Wsign-conversion -O0 -g
R_FLAGS := -std=c++20 -O2
ARGS := 1 0.4 U 2000 2000 2000 ./

LENGTHS := 30 40 50 60 70 80 90 100 110 120
ALGORITHMS := single line
INTERACTIONS := -0.5

# build
all: $(D_TRGT)

$(D_TRGT): $(SRC) $(HDR)
	$(CXX) $(D_FLAGS) $(SRC) -o $(D_TRGT)
	@echo "Running debug build..."
	@time ./$(D_TRGT) $(ARGS)
	@$(MAKE) test

release: 
	@for L in $(LENGTHS); do\
		for A in $(ALGORITHMS); do\
			for I in $(INTERACTIONS); do\
				if [ "$$A" = "line" ]; then \
					LINEUPDATE=true; \
				else \
					LINEUPDATE=false; \
				fi; \
				DEFS="-DLATTICE_LENGTH=$$L -DLINEUPDATE=$$LINEUPDATE -DNNN_INTERACTION=$$I"; \
				$(CXX) $(R_FLAGS) $$DEFS $(SRC) -o $(BINARIES)/egen$${L}$${A}$${I}; \
			done;\
		done;\
	done


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
