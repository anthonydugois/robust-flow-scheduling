LATEX = latexmk
BUILD = build

ALL_TEX = $(wildcard *.tex)
ALL_PDF = $(patsubst %.tex, %.pdf, $(ALL_TEX))

all: $(ALL_PDF)

%.pdf: %.tex $(BUILD)
	$(LATEX) -quiet -pdf -outdir=$(BUILD) $<

$(BUILD):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD)
