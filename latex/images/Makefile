SVGFILES := $(wildcard *.svg)
OBJECTS := $(patsubst %.svg,%.eps,$(SVGFILES))

all: $(OBJECTS)

%.eps: %.svg
	rsvg-convert -f eps -o $@ $<

clean:
	@rm -rf $(OBJECTS) $(patsubst %.eps,%-eps-converted-to.pdf,$(OBJECTS))
