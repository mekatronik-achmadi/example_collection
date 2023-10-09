TEXCC=pdflatex
BIBCC=bibtex
TEXFLAGS=-shell-escape -synctex=1 -interaction=nonstopmode
TEXFILE=$(shell basename --suffix=.tex $$(ls -1 *.tex))

# '-' sign mean keep going even if the command fail
all:
	-$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex
	-$(BIBCC) $(TEXFILE).aux
	-$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex
	-$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex # run twice to update ToC/BibTeX

clean:
	rm -f *.out *.bbl *.blg *.lof *.lot *.nav *.vrb
	rm -f *.log *.toc *.synctex.gz  *.pyg *.snm
	rm -f *.aux *Notes.bib
	rm -f *.pdf
	rm -rf ./_minted*
