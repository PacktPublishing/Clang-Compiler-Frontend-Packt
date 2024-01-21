HEADERS=$(wildcard ./*.h)
PCHS=$(HEADERS:.h=.pch)
CLANG=~/local/llvm-project/build/bin/clang

%.pch: %.h
	$(CLANG) -x c++-header $< -o $@

pch: $(PCHS)

exe: main.cpp pch
	$(CLANG) -include-pch header.pch main.cpp -o main -lstdc++


all: pch exe

clean:
	rm -rf *~ *.dSYM *.pch main
