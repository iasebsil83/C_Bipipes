// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




//bipipes utility
#include "../../lib/bipipes.h"








// ---------------- DEBUG SHORTCUTS ----------------

//read - write in bipipe with debug text
void ____read(bipipe* bp){

	//read data from bipipe
	char* data = bipipe_read(bp);

	//show data
	if(data == NULL){
		printf("Prog_2 > PID[%i], PPID[%i] : Reading in bipipe [%s] : NULL.\n", getpid(), getppid(), bp->info);
	}else{
		printf("Prog_2 > PID[%i], PPID[%i] : Reading in bipipe [%s] : \"", getpid(), getppid(), bp->info);
		for(int c=0; c < bp->length; c++){
			printf("%c", data[c]);
		}
		printf("\".\n");
	}
}

void ____write(bipipe* bp, char* data){

	//write data in bipipe
	bipipe_write(bp, data);
	printf("Prog_2 > PID[%i], PPID[%i] : Writing in bipipe [%s] : \"%s\".\n", getpid(), getppid(), bp->info, data);
}




//sleep with float value
void ____sleep(float duration){
	usleep(duration*1000000);
}








// ---------------- EXECUTION ----------------

//main
int main(int argc, char** argv){

	//BIPIPE

	//get bipipe info (passed as argument)
	bipipe* bp = bipipe_join(argv[1]);
	printf("Prog_2 > PID[%i], PPID[%i] : Joined bipipe [%s].\n", getpid(), getppid(), argv[1]);



	//DATA EXCHANGES

	//test procedure (P & P1 runs in parallel)
	____sleep(12.5);

	____read(bp);   //must be "_ Test for P2 _"
	____sleep(2.5);

	____write(bp,"P2 has received");
	____sleep(7.5);



	//LIBERATE

	//free data
	printf("Prog_2 > PID[%i], PPID[%i] : Deleting bipipe...\n", getpid(), getppid());
	bipipe_delete(bp);
	printf("Prog_2 > PID[%i], PPID[%i] : Bipipe deleted.\n", getpid(), getppid());



	return EXIT_SUCCESS;
}
