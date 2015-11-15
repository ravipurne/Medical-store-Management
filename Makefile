program: fun.o main.o
	cc fun.o main.o -o program
main.o: haider.h main.c
	cc -c -Wall main.c
fun.o: haider.h fun.c
	cc -c -Wall fun.c
