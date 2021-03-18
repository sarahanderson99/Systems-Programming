/*
NAME Sarah Anderson (sca2)
CLASS ECE 2220
PROJECT Signals "Base to Submarines"
PURPOSE The purpose of this program is for the user to open four terminals windows and in the first window it will reprsent the base and the other three will represent submarines. It moves the submareis a certain distance out and it gives them random amounts of fuel and the progam will see how many of the three submarines that will make it back safely. 
ASSUMPTIONS I am assuming that the person running the program knows to start with four terminal windows open and knows the commands to run the program. No known problems at this time.
*/

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#define MAX_PROCESSES 10
#define INITAL_DISTANCE 0

//This allows us to know what type of computer the person is running and it adjusts according to the computer OS
enum Computers {
	PC, MAC, OS
};

//Allows us to have other exit codes to suggest what happened during the program
enum ExitCodes
{	EXIT_CRASHED, EXIT_SUCESS, EXITS
};

//Initializing the vairables used in this program
int PID[MAX_PROCESSES], ChildPID;
int Terminal[MAX_PROCESSES];
int Terminals = 0;
int Fuel, Distance;
int Processes, Process;
FILE *fpr[MAX_PROCESSES];
int Bombs;
int Computer;
typedef void (*fptr)();

//Protypes
void Alarm(int signum);
void Bomb (int signum);
void Refuel (int signum);
void ChildrenStuff(void);
void Monitor(void);
void PrintExit(int p, int status);
void FindTerminals(void);
void ParentStuff(void);
int CloseTerminals(void);

int main (int argc, char *argv[]){

	int i = 0;
	int Parent = 1;
	
	//prints out the starting time of the program
	time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	char s[64];
    	assert(strftime(s, sizeof(s), "%c", tm));
    	printf("Starting time is %s\n", s);

	//Checks to see if the computer is a PC or a MAC
	if(argc == 2){
		if(strcmp(argv[1], "MAC") == 0){
			Computer = MAC;
		}
		else{
			Computer = PC;
		}
	}	

	//Opens up the termianls we are going to use
	FindTerminals();

	//Gets the PID of all the children
	PID[Process = 0] = getpid();

	//Creates three different submarines
	for(i = 1; i <= 3; i++){
		if(Parent){
			PID[Process = i] = fork();
			if(PID[i] == 0){
				Parent = 0;
				printf("Creating child number %d\n", i);
				ChildrenStuff();
			}
			else{
				printf("Child %d Created\n", i);
			}
		}
	}

	//Does the parent stuff also monitors the children
	if(Parent){
		PID[4] = fork();
		if(PID[4] == 0){
			Monitor();
		}
		else{
			ParentStuff();
			kill(PID[4], 1);
			CloseTerminals();
		}
	}
return 0;
}

//Alarm that controls when the submarines are going to be bombed, refueled, etc.
void Alarm(int signum){

	static int display, add_distance;

	//Checks the fuel level of each of the submarines
	if(--Fuel < 0){
		Fuel = 0;
	}

	//Checks to see if it needs to add distance or not
	if(++add_distance == 2){
		add_distance = 0;
		if(Bombs == 0){
			Distance--;
		}
		else{
			Distance++;
		}
	}

	//Displays the amount of fuel left, the PID, the distance, etc. into the approprate terminal
	if(++display == 3){
		display = 0;
		fprintf(fpr[Process], "T%d:P%d Bomber %d: Fuel = %d gal, Distance = %d mi.\n", Terminal[Process],ChildPID % 10, Process, Fuel, Distance);
	}
	
	//if there is no fuel left it tells that the submarine is down and that it lost all fuel
	if(Fuel == 0){
		fprintf(fpr[Process], "Bomber %d Down, We have lost all fuel...\n", Process);
		exit(EXIT_CRASHED);
	}	
	
	//If the fuel is under a certain amount it prints out to the screen that the fuel is almost gone 
	else if(Fuel < 5){
		fprintf(fpr[Process], "Mayday....This is bomber %d. Fuel is alomost gone.\n", Process);
	}
	
	//Prints out final things telling the runner that it was a close call
	if((Bombs == 0) && (Distance == 0)){
		fprintf(fpr[Process], "Mission Complete\n");
		if(Fuel <= 5){
			fprintf(fpr[Process], "That was a close call\n");
		}
		exit(EXIT_SUCESS);
	}

	alarm(1);
}

//Bombs the submarine
void Bomb (int signum){
	if(Bombs > 0){
		//prints out to the screen that a bomb is being dropped
		fprintf(fpr[Process], "Bomber %d dropping ordinance\n", Process);
		if((Bomb - 1) == 0){
			fprintf(fpr[Process], "Bomber %d returning to base.\n", Process);
		}
	}
	//No more bombs are left
	else{
		fprintf(fpr[Process], "Bomber %d has no ordinace.\n", Process);
	}
}

//Refuels the submarine
void Refuel (int signum){

	Fuel = 50;
	fprintf(fpr[Process], "Plane %d to base: Thank you for more fuel\n", Process);
}

//Performs the tasks set by the parent to do on the three differnt submarines
void ChildrenStuff(void){
	//seeding for random number. This will allow for different random numbers each time the program is ran
	srand(time(0));

	ChildPID = getpid();
	signal(SIGALRM, (fptr)Alarm);
	signal(SIGUSR2, (fptr)Bomb);
	signal(SIGUSR1, (fptr)Refuel);
	//random number between 1000 and 5000
	Fuel = (rand() % 5000) + 1000;
	//Random number of bombs set between 6 and 10
	Bombs = (rand() % 10) + 6;
	Distance = INITAL_DISTANCE;
	alarm(1);
}

//Preforms the command that are typed into the terminals by the person running the program
void Monitor(void){
	char strIn[10];
	int p;

	Processes = 3;
	//Gets the command from the user
	while(Processes > 0){
		scanf("%s", strIn);
		fflush(stdin);
		
		if(strlen(strIn) == 2){
			p = atoi(&strIn[1]);
			if((p > 0) && (p < 4)){
				//This switch statment performs the command on the certain ship set by the person running the program
				switch(strIn[0]){
					//kill the certain submarine 
					case 's':
						kill(PID[p], 1);
						printf("Child %d was kiled\n", p);
						Processes--;
						break;
					//refuel the submarine
					case 'r':
						kill(PID[p], SIGUSR1);
						break;
					//bomb the submarine 
					case 'l':
						kill(PID[p], SIGUSR2);
						break;
				}
			}
			//Checks to make sure that the bomb number is vaild
			else{
				printf("Not a vaild bomber number\n");
			}
		}
		//Kills all the other submarines if q is entered
		else if(strlen(strIn) == 1){
			if(strIn[0] == 'q'){
				for(p = 1; p <= 3; p++){
					kill(PID[p], 1);
					Processes--;
				}
			}
		}
	}
}

//prints out the final exit codes to the console
void PrintExit(int p, int status){
	char exit_byte, signal_byte, core_bit;

	exit_byte = status >> 8;
	signal_byte = status & 0x7f;
	core_bit = status & 0x80;

	printf("Child status exit = %d, signal = %d, core = %d\n", exit_byte, signal_byte, core_bit);
	
	if(exit_byte == EXIT_SUCCESS){
		printf("Process %d mission was a success\n", p%10);
	}
	else{
		printf("Process %d mission was a failure\n", p%10);
	}
}

//Does what parents do
void ParentStuff(void){
	int i;
	int child_status[MAX_PROCESSES], wait_ret[MAX_PROCESSES];
	
	//Waits on the child to perform its processes and then it moves on to the next one
	wait_ret[1] = wait(&child_status[1]);
	wait_ret[2] = wait(&child_status[2]);
	wait_ret[3] = wait(&child_status[3]);

	//Prints out the final print statemnt telling if it was a success or not
	for(i = 1; i <= 3; i++){
		PrintExit(wait_ret[i], child_status[i]);
	}
}

const char *strDir[OS] = {"/dev/pts/", "/dev/ttys"};

void FindTerminals(void){
	int i;
	char strDev[100];
	
	//Checks to make sure that it is the correct computer and opens 100 terminals 
	for(i = 0; i < 100; i++){
		if(Computer == MAC) sprintf(strDev, "%s%03d", strDir[Computer], i);
		else sprintf(strDev, "%s%d", strDir[PC], i);

		printf("Opening %s...\n", strDev); fflush(stdout);
	
		if((fpr[Terminals] = fopen(strDev, "w")) == NULL){
//			printf("Unable to open terminal\n");
		//	exit(0);
		}
		else{
			Terminal[Terminals] = i;
			Terminals++;
		}
	}

	//prints out the working termianls for the program
	printf("Terminals are now all ready...\n");
	for(i = 0; i < Terminals; i++){
		printf("Terminal[%d] = %d\n", i, Terminal[i]);
	}
	printf("\n");
}

//Closes all working terminals and prints out the final time
int CloseTerminals(void){
	int i;
	
	//Closes all working termianls
	for(i = 0; i < Terminals; i++){
		fclose(fpr[i]);
	}

	//Prints out eh final time of the program
	time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[64];
        assert(strftime(s, sizeof(s), "%c", tm));
        printf("Ending time is %s\n", s);
	
return 0;
}	
