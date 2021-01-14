#executable
run: program1.o bipipes.o
	gcc -Wall -o run program1.o bipipes.o -O2
	rm -f *.o



#program
program1.o: program1.c ../../bipipes.h
	gcc -c program1.c -O2



#bipipes library
bipipes.o: ../../bipipes.c ../../bipipes.h
	gcc -Wall -c ../../bipipes.c -O2
