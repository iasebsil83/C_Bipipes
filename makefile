#executables
run: bipipes.o processes.o more_strings.o prog.o
	gcc -Wall -o run prog.o more_strings.o processes.o bipipes.o -O2
	rm -f *.o



#example program
prog.o: prog.c bipipes.h src/processes.h
	gcc -Wall -c prog.c -O2



#bipipes library
bipipes.o: bipipes.c bipipes.h
	gcc -Wall -c bipipes.c -O2



#processes library
processes.o: src/processes.c src/processes.h
	gcc -Wall -c src/processes.c -O2



#more_strings library
more_strings.o: src/more_strings.c src/more_strings.h
	gcc -Wall -c src/more_strings.c -O2
