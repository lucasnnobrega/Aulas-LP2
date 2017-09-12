OBJFILES = ${wildcard ./*.cpp}

all:
	g++ -std=c++14 -ggdb -O0 -pthread ${OBJFILES} -o main
	./main
clear:
	rm -rf *.o
