HEADERS=$(wildcard ./*.h)
CLANG=../../../../../llvm-project/install/bin/clang

all: main.o
	$(CLANG) main.o -o main -lstdc++

main.o: main.cpp $(HEADERS)
	$(CLANG) -cc1 -emit-obj main.cpp -fmodules -fmodule-map-file=module.modulemap -fmodules-cache-path=./cache -o main.o

clean:
	rm -rf *~ *.dSYM *.pch mainpch mainpcm main *.pcm *.tmp *.o cache
