report := report.tex
content := $(wildcard content/*.tex)
title := $(wildcard title/*.tex)
docs := $(report) $(content) $(title)

report_output := report.pdf

BUILD_DIR := build

all: mkdir $(report_output)

$(report_output): build/report.pdf
	cp build/report.pdf ./

build/report.pdf: $(docs)
	xelatex -output-directory=build/ $(report)
	xelatex -output-directory=build/ $(report)

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

clean:
	rm -rf $(BUILD_DIR)/*
