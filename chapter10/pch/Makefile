# header1.pch: header1.h
# 	clang++ -x c++-header header1.h -o header1.pch 
# header2.pch: header2.h
# 	clang++ -x c++-header header2.h -o header2.pch -include-pch header1.pch 


HEADERS=$(wildcard ./*.h)
PCHS=$(HEADERS:.h=.pch)
%.pch: %.h
	clang -x c++-header $< -o $@



pch: $(PCHS)

exe: main.cpp
	clang -include-pch header1.pch -include-pch header2.pch main.cpp -o main -lstdc++

exenopch: main.cpp
	clang++ main.cpp -o main -lstdc++


all: pch exe

clean:
	rm -rf *~ *.dSYM *.pch main
