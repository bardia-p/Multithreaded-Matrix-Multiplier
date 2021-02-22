// Bardia Parmoun
// 101143006

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/shm.h>

#include "shm_shared.h"

#define MICRO_SEC_IN_SEC 1000000

static int matrixDone;
static double new_row[MATRIX_SIZE];

/* Tells the parent to proceed if all the child processes are done */
void callParent (int sig){
	matrixDone =1;
}

/* Multiplies a given row of matrix M with the entire matrix N */
void multiplyRow (double* row){
	for (int i = 0; i < MATRIX_SIZE; i++){
		new_row[i]=0;
		for (int j=0; j < MATRIX_SIZE; j++){
			new_row[i] += N_MATRIX[j][i] * row[j]; 
		}
	}
}

/* Prints the matrix given a matrix */
void printMatrix (double matrix[][MATRIX_SIZE]){
	for (int i=0; i<MATRIX_SIZE; i++){
		printf("[");
		for (int j=0; j<MATRIX_SIZE; j++){
			printf("%10.2lf ", matrix[i][j]);
		}
		printf("]\n");
	}	
}

/* Prints the largest number in a given row */
double largestNumber (double* row){
	double max = row[0];
	for (int i=1; i<MATRIX_SIZE; i++){
		if (row[i]>max){
			max = row[i];
		}
	}
	return max;
}


int main ()
{
	pid_t pid;

	struct timeval start, end;	
	gettimeofday(&start, NULL);

	printf("Matrix multiplier program starting\n");
	
	// Printing matrix M
	printf("Multiplying matrix M: \n");
	printMatrix (M_MATRIX);

	// Printing matrix N
	printf("with matrix N: \n");
	printMatrix (N_MATRIX);

	matrixDone = 0;

	// creates a shared memory
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	int shmid;

	// connects the memory to the process
	shmid = shmget ((key_t)5080, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
				
	if (shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
				
	shared_memory = shmat (shmid, (void *)0, 0);

	//printf("Memory attached at %X\n", (int) shared_memory);

	shared_stuff = (struct shared_use_st *) shared_memory;

	shared_stuff ->rowsVisited =0;
	
	// forks a new child 
	for (int i = 0; i < MATRIX_SIZE; i++){
		pid = fork();
		switch (pid){
			case 0:
				
				printf("Child Process: working with row %d\n", i+1);

				// creates a shared memory
				void *shared_memory = (void *)0;
				struct shared_use_st *shared_stuff;
				int shmid;



				// connects the memory to the process
				shmid = shmget ((key_t)5080, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
				
				if (shmid == -1){
					fprintf(stderr, "shmget failed\n");
					exit(EXIT_FAILURE);
				}
				
				shared_memory = shmat (shmid, (void *)0, 0);

				// printf("Memory attached at %X\n", (int) shared_memory);

				shared_stuff = (struct shared_use_st *) shared_memory;

				// Multiplies row i of matrix M with the entire matrix N
				multiplyRow(M_MATRIX[i]);
				
				while (shared_stuff -> isMemoryFull){};

				// Enters the critical region
				shared_stuff->isMemoryFull = 1;
				for (int j=0; j<MATRIX_SIZE; j++){
					shared_stuff->Q_MATRIX[i][j] = new_row[j];
				}
						
						
				// Used to keep track of the rows that have been visited 
				shared_stuff ->rowsVisited +=1;
		
				shared_stuff -> isMemoryFull = 0;
				// Exits the cricitcal region 

				// Finding the largest number in row i of matrix Q		
				shared_stuff->maxValues[i] =  largestNumber(shared_stuff->Q_MATRIX[i]);
				printf("The largest number in row %d of matrix Q is %.2lf\n", i+1, shared_stuff->maxValues[i]);
			
				// Signals the parent if all the rows have been visited
				if (shared_stuff -> rowsVisited == MATRIX_SIZE){
					// signals the parents
					kill(getppid(), SIGALRM);
				
				}
				// detaches the memory
				if (shmdt(shared_memory)==-1){
					fprintf(stderr, "shmdt failed\n");
					exit(EXIT_FAILURE);
				}

				// ends the child process
				exit(0);

			case -1:
				perror("fork failed");
				exit(1);
		}
	}
	

		
	// parent code	
	// The parent waiting for the child's signal
	(void) signal (SIGALRM, callParent);

	pause();		
		
	printf("Final Result\n");
	if (matrixDone){
		printMatrix (shared_stuff->Q_MATRIX);
		printf("The largest number in the matrix is %.2lf\n", largestNumber(shared_stuff->maxValues));
			
		gettimeofday(&end, NULL);

		printf("The time it took to run the program in micro sec %ld\n", (end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec) -
									      (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec));
			
		// detaches the memory
		if (shmdt(shared_memory)==-1){
			fprintf(stderr, "shmdt failed\n");
			exit(EXIT_FAILURE);
		}
		
		// deletes the memory
		if (shmctl(shmid, IPC_RMID, 0) == -1){
			fprintf(stderr, "shmctl(IPC_RMID) failed\n");
			exit(EXIT_FAILURE);
		}
	}
		

	exit(0);
}
