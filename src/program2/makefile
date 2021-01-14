#executable
run: program2.o bipipes.o
	gcc -Wall -o run program2.o bipipes.o -O2
	rm -f *.o



#program
program2.o: program2.c ../../bipipes.h
	gcc -c program2.c -O2



#bipipes library
bipipes.o: ../../bipipes.c ../../bipipes.h
	gcc -Wall -c ../../bipipes.c -O2
