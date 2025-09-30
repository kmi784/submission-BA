FLAGS:=-synctex=1 -shell-escape -output-directory=auxiliary 
TEXDIRS:=formal results theory images
PLTDIR:=plots
IMGDIR:=images

TEXFILES:=$(foreach D,$(TEXDIRS),$(wildcard $(D)/*.tex))
GPFILES:=$(filter-out $(PLTDIR)/include.gp,$(wildcard $(PLTDIR)/*.gp))
SVGFILES:=$(wildcard $(IMGDIR)/*.svg)


all: auxiliary/main.pdf 
	@evince main.pdf &

# document
auxiliary/main.pdf: main.tex $(TEXFILES) $(patsubst %.gp,%.eps,$(GPFILES)) $(patsubst %.svg,%.eps,$(SVGFILES))
	@mkdir -p auxiliary
	@pdflatex $(FLAGS) main 
	@cp auxiliary/main.pdf ./

# plots 
$(PLTDIR)/%.eps: $(PLTDIR)/%.gp 
	@$(MAKE) --directory=$(PLTDIR)

# images
$(IMGDIR)/%.eps: $(IMGDIR)/%.svg 
	@$(MAKE) --directory=$(IMGDIR)

clean:
	@$(MAKE) clean --directory=$(PLTDIR)
	@$(MAKE) clean --directory=$(IMGDIR)
	@rm -rf auxiliary

bib:
	bibtex auxiliary/main     
