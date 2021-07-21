#executables
run: bipipes.o processes.o prog.o

	@#compile the 1st external program
	@echo "\nCompiling external program 1..."
	gcc -Wall -o src/program1/run src/program1/program1.c bipipes.o -O2
	@echo "done.\n"

	@#compile the 2nd external program
	@echo "Compiling external program 2..."
	gcc -Wall -o src/program2/run src/program2/program2.c bipipes.o -O2
	@echo "done.\n"

	@#compile example program
	@echo "Compiling example program..."
	gcc -Wall -o run prog.o processes.o bipipes.o -O2
	rm -f *.o



#example program
prog.o: src/prog.c lib/bipipes.h lib/processes.h
	gcc -Wall -c src/prog.c -O2



#libraries
bipipes.o: lib/bipipes.c lib/bipipes.h
	gcc -Wall -c lib/bipipes.c -O2

processes.o: lib/processes.c lib/processes.h
	gcc -Wall -c lib/processes.c -O2



#clean option
clean:
	rm run src/program1/run src/program2/run
