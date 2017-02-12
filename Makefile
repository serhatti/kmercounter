#serhat : modified original kseq file ....
LIBBF=external/install/libbf
SPHASH=external/install/sparsehash
CC=g++
#CC=clang++

all:
	$(CC) -O3 anyoption.cxx KmerCounter.cxx main.cpp -o main.exe -I$(SPHASH)/include -I$(LIBBF)/include -lz -std=c++11 -L$(LIBBF)/lib -lbf
clean:
		rm -f  main.exe

