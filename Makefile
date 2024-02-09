LATEX = latexmk
BUILD = build

notes: notes.pdf

%.pdf: %.tex
	mkdir -p $(BUILD)
	$(LATEX) -pdf -outdir=$(BUILD) $<

clean:
	rm -rf $(BUILD)
