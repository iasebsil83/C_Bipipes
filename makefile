#executables
run: bipipes.o processes.o prog.o
	gcc -Wall -o run prog.o processes.o bipipes.o -O2
	rm -f *.o



#example program
prog.o: prog.c bipipes.h src/processes.h
	gcc -Wall -c prog.c -O2



#libraries
bipipes.o: bipipes.c bipipes.h
	gcc -Wall -c bipipes.c -O2

processes.o: src/processes.c src/processes.h
	gcc -Wall -c src/processes.c -O2
