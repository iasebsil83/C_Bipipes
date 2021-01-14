// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



//processes
#include "src/processes.h"



//string utilities
#include "src/more_strings.h"



//bipipes utility
#include "bipipes.h"




















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

    Contact     : 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




















// ---------------- DEBUG SHORTCUTS ----------------

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

	//prepare subprocess 1 command-line
	char* p1_cmdLine = malloc(45); //will contain a string like "run 0a0a0a0a1b1b1b1b2c2c2c2c3d3d3d3d4e4e4e4e"
	if(p1_cmdLine == NULL){
		printf("FATAL ERROR > prog.c : main() : PID[%i], PPID[%i] : Computer refuses to give more memory.\n", getpid(), getppid());
		exit(EXIT_FAILURE);
	}
	sprintf(p1_cmdLine, "run %s", bp1->info);

	//prepare subprocess 1 command-array
	char** p1_cmd = strArr_split(
		p1_cmdLine,
		' '
	);
	free(p1_cmdLine); //no longer useful

	//create subprocess 1
	proc* p1 = proc_create(
		"src/program1/run",
		p1_cmd
	);
	printf("Prog   > PID[%i], PPID[%i] : Subprocess 1 created (./src/program1/run %s).\n", getpid(), getppid(), bp1->info);






	//SUBPROCESS 2

	//prepare subprocess 2 command-line
	char* p2_cmdLine = malloc(45); //will contain a string like "run 0a0a0a0a1b1b1b1b2c2c2c2c3d3d3d3d4e4e4e4e"
	if(p2_cmdLine == NULL){
		printf("FATAL ERROR > prog.c : main() : PID[%i], PPID[%i] : Computer refuses to give more memory.\n", getpid(), getppid());
		exit(EXIT_FAILURE);
	}
	sprintf(p2_cmdLine, "run %s", bp2->info);

	//prepare subprocess 2 command-array
	char** p2_cmd = strArr_split(
		p2_cmdLine,
		' '
	);
	free(p2_cmdLine); //no longer useful

	//create subprocess 2
	proc* p2 = proc_create(
		"src/program2/run",
		p2_cmd
	);
	printf("Prog   > PID[%i], PPID[%i] : Subprocess 2 created (./src/program2/run %s).\n", getpid(), getppid(), bp2->info);






	//LAUNCH PROCESSES

	//start processes
	printf("Prog   > PID[%i], PPID[%i] : Launching processes...\n", getpid(), getppid());
	proc_start(p1);
	proc_start(p2);
	printf("Prog   > PID[%i], PPID[%i] : Processes launched => Activation of bipipes from parent side...\n", getpid(), getppid());

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
	proc_stop(p1);
	proc_stop(p2);
	printf("Prog   > PID[%i], PPID[%i] : Subprocesses killed.\n", getpid(), getppid());
	strArr_free(p1_cmd);
	strArr_free(p2_cmd);






	return EXIT_SUCCESS;
}
