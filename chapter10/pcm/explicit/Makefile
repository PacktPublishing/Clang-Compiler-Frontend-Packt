HEADERS=$(wildcard ./*.h)
CLANG=../../../../../llvm-project/install/bin/clang

PCMS=$(HEADERS:.h=.pcm)

all: main.o
	$(CLANG) main.o -o main -lstdc++

main.o: main.cpp pcm
	$(CLANG) -cc1 -emit-obj main.cpp -fmodules -fmodule-map-file=module.modulemap -fmodule-file=header1=header1.pcm -fmodule-file=header2=header2.pcm -o main.o -fno-implicit-modules

%.pcm: %.h
	$(CLANG) -cc1 -x c++-header -emit-module -o $@ -fmodules module.modulemap -fmodule-name=$(basename $<) -fno-implicit-modules

pcm: $(PCMS)

clean:
	rm -rf *~ *.dSYM *.pch mainpch mainpcm main *.pcm *.tmp *.o
