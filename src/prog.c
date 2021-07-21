// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



//processes
#include "../lib/processes.h"



//bipipes utility
#include "../lib/bipipes.h"












/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        bipipes.h demonstration program

        Blablabla about the subject.

    DD/MM/YYYY > [V.V.V] :
    - Added something.
    - Added something else.

    DD/MM/YYYY > [V.V.V] :
    - Added something that wasn't before.
    - Fixed a bug.
    - Added something else.
    - Added something else again.

    BUGS : Active bugs in last version.
    NOTES : Notes.

    Contact     : ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */












// ---------------- DEBUG SHORTCUTS ----------------

//malloc a string
char* malloc_string(char* s){
	char* newS = malloc(strlen(s));
	if(newS == NULL){
		printf("FATAL ERROR > prog.c : malloc_string() : PID[%i], PPID[%i] : Computer refuses to give more memory.\n", getpid(), getppid());
		exit(EXIT_FAILURE);
	}

	//write into newS
	sprintf(newS, "%s", s);
	return newS;
}



//read - write in bipipe with debug text
void ____read(bipipe* bp){

	//read data from bipipe
	char* data = bipipe_read(bp);

	//show data
	if(data == NULL){
		printf("Prog   > PID[%i], PPID[%i] : Reading in bipipe [%s] : NULL.\n", getpid(), getppid(), bp->info);
	}else{
		printf("Prog   > PID[%i], PPID[%i] : Reading in bipipe [%s] : \"", getpid(), getppid(), bp->info);
		for(int c=0; c < bp->length; c++){
			printf("%c", data[c]);
		}
		printf("\".\n");
	}
}

void ____write(bipipe* bp, char* data){

	//write data in bipipe
	bipipe_write(bp, data);
	printf("Prog   > PID[%i], PPID[%i] : Writing in bipipe [%s] : \"%s\".\n", getpid(), getppid(), bp->info, data);
}



//sleep with float value
void ____sleep(float duration){
	usleep(duration*1000000);
}












// ---------------- EXECUTION ----------------

//main
int main(){
	//presentation
	printf("Prog   > PID[%i], PPID[%i] : This is a basic example of pipe manipulation using \"bipipes.c/.h\".\n\n", getpid(), getppid());



	//BIPIPES

	//create a first bipipe
	bipipe* bp1 = bipipe_create(16);
	printf("Prog   > PID[%i], PPID[%i] : 1st bipipe created (length %u, info [%s]).\n", getpid(), getppid(), bp1->length, bp1->info);

	//create a second bipipe
	bipipe* bp2 = bipipe_create(16);
	printf("Prog   > PID[%i], PPID[%i] : 2nd bipipe created (length %u, info [%s]).\n", getpid(), getppid(), bp2->length, bp2->info);



	//SUBPROCESS 1

	//prepare subprocess 1 command (will be like {"run","0a0a0a0a1b1b1b1b2c2c2c2c3d3d3d3d4e4e4e4e", NULL})
	char** p1_cmd = malloc(3*sizeof(char*));
	if(p1_cmd == NULL){
		printf("FATAL ERROR > prog.c : main() : PID[%i], PPID[%i] : Computer refuses to give more memory.\n", getpid(), getppid());
		exit(EXIT_FAILURE);
	}
	p1_cmd[0] = malloc_string("run");
	p1_cmd[1] = malloc_string(bp1->info);
	p1_cmd[2] = NULL;

	//create subprocess 1
	proc* p1 = proc_create(
		"src/program1/run",
		p1_cmd
	);
	printf("Prog   > PID[%i], PPID[%i] : Subprocess 1 created (./src/program1/run %s).\n", getpid(), getppid(), bp1->info);



	//SUBPROCESS 2

	//prepare subprocess 2 command (will be like {"run","0a0a0a0a1b1b1b1b2c2c2c2c3d3d3d3d4e4e4e4e", NULL})
	char** p2_cmd = malloc(3*sizeof(char*));
	if(p2_cmd == NULL){
		printf("FATAL ERROR > prog.c : main() : PID[%i], PPID[%i] : Computer refuses to give more memory.\n", getpid(), getppid());
		exit(EXIT_FAILURE);
	}
	p2_cmd[0] = malloc_string("run");
	p2_cmd[1] = malloc_string(bp2->info);
	p2_cmd[2] = NULL;

	//create subprocess 2
	proc* p2 = proc_create(
		"src/program2/run",
		p2_cmd
	);
	printf("Prog   > PID[%i], PPID[%i] : Subprocess 2 created (./src/program2/run %s).\n", getpid(), getppid(), bp2->info);



	//LAUNCH PROCESSES

	//start processes
	printf("Prog   > PID[%i], PPID[%i] : Launching processes...\n\n", getpid(), getppid());
	proc_start(p1);
	proc_start(p2);
	usleep(500000); //wait a bit to let subprocesses be launched
	printf("\nProg   > PID[%i], PPID[%i] : Processes launched => Activation of bipipes from parent side...\n", getpid(), getppid());

	//activate bipipes
	bipipe_everybodyJoined(bp1);
	bipipe_everybodyJoined(bp2);
	printf("Prog   > PID[%i], PPID[%i] : Bipipes activated from parent side, my children can now communicate with me.\n\n", getpid(), getppid());



	//DATA EXCHANGES

	//test procedure (p1 & p2 runs in parallel)
	____write(bp1,"_ Test for P1 _");
	____sleep(7.5);

	____read(bp1);  //must have "P1 has received"
	____sleep(2.5);

	____write(bp2,"_ Test for P2 _");
	____sleep(7.5);

	____read(bp2);  //must have "P2 has received"
	____sleep(7.5);



	//TERMINATE

	//free bipipes
	printf("Prog   > PID[%i], PPID[%i] : Deleting bipipes...\n", getpid(), getppid());
	bipipe_delete(bp1);
	bipipe_delete(bp2);

	//kill subprocesses
	printf("Prog   > PID[%i], PPID[%i] : Bipipes deleted => Killing subprocesses...\n", getpid(), getppid());
	proc_stop(p1, PROC__STOP_KILL);
	proc_stop(p2, PROC__STOP_KILL);
	printf("Prog   > PID[%i], PPID[%i] : Subprocesses killed.\n", getpid(), getppid());
	proc_delete(p1);
	proc_delete(p2);



	return EXIT_SUCCESS;
}
