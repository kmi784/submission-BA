PLOT_DIR := plots
BIB := refernces.bib
FLAGS := -synctex=1 -shell-escape -output-directory auxiliary 

default: auxiliary/main.pdf 
	evince main.pdf &

auxiliary/main.pdf: main.tex formal/*.tex results/*.tex theory/*.tex images/*.tex 
	mkdir -p auxiliary
	pdflatex $(FLAGS) main
	cp auxiliary/main.pdf ./

clean:
	rm -rf auxiliary

bib:
	bibtex auxiliary/main
	pdflatex $(FLAGS) main
	pdflatex $(FLAGS) main

plot:
	$(MAKE) --directory=$(PLOT_DIR)
	pdflatex $(FLAGS) main
	cp auxiliary/main.pdf main.pdf


plotclean:
	$(MAKE) clean --directory=$(PLOT_DIR)


