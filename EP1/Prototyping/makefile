OBJFILES = ${wildcard ./*.cpp}

all:
	g++ -std=c++14 -ggdb -pthread ${OBJFILES} -o main
	./main
clear:
	rm -rf *.o
