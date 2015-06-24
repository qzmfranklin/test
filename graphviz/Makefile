DOT:=dot

OUTPUT_FORMAT:=pdf

SOURCE_GV:=$(wildcard *.gv)
SOURCE_DOT:=$(wildcard *.dot)
OUTPUT:=$(SOURCE_GV:%.gv=%.$(OUTPUT_FORMAT)) \
	$(SOURCE_DOT:%.dot=%.$(OUTPUT_FORMAT))

.SUFFIXES:

.PHONY: all clean

all: $(OUTPUT)

clean:
	rm -f $(OUTPUT)

%.$(OUTPUT_FORMAT): %.gv
	$(DOT) -T$(OUTPUT_FORMAT) $< -o $@

%.$(OUTPUT_FORMAT): %.dot
	$(DOT) -T$(OUTPUT_FORMAT) $< -o $@
