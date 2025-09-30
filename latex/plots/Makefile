GPDIRS=.
INCFILE=./include.gp
TEMPLATEFILE=./template.gp

# for-style iteration (foreach) and regular expression completions (wildcard)
GPFILES=$(foreach D,$(GPDIRS),$(wildcard $(D)/*.gp))
T:=$(filter-out $(INCFILE),$(GPFILES))
GPFILES=$T
T:=$(filter-out $(TEMPLATEFILE),$(GPFILES))
GPFILES=$T

# regular expression replacement
OBJECTS=$(patsubst %.gp,%.eps,$(GPFILES))

all: $(OBJECTS)

%.eps:%.gp $(INCFILE)
	@gnuplot $<
	@latex $(patsubst %.gp,%.tex,$<)
	@dvips $(patsubst %.gp,%.dvi,$<)
	@mv $(patsubst %.gp,%.ps,$<) $(patsubst %.gp,%.eps,$<)
	@rm $(patsubst %.gp,%.dvi,$<) $(patsubst %.gp,%.aux,$<) $(patsubst %.gp,%-inc.eps,$<) $(patsubst %.gp,%.log,$<) $(patsubst %.gp,%.tex,$<)

clean:
	@rm -rf $(OBJECTS) $(patsubst %.eps,%-eps-converted-to.pdf,$(OBJECTS))

