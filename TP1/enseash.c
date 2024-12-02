#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// In this code we print messages then
// wait for the user to type in order to exit
// the program

// On the terminal first type:
// 	gcc -o enseash enseash.c
//in order to compile it
//then type:
//	./enseash 
//to land the executable.



/*
*	Call of the different command of the user to the OS
*/
void call_Command(char command[25]){
	int cr = system( command);
	if ( cr != 0 ) {
		fprintf( stderr,"Impossible de lancer la commande : %s\n",command );
	}
}

void exit_command(char command[25]){
	int comparString;

	comparString=strcmp(command,"exit");
	if(comparString == 0){
		exit(0);
	}	
}


void enseash(){
	printf("Welcome to ENSEA Tiny SHell\n");
	printf("Type 'exit' to quit\n");	
	char typed_return[25];

	while(1){
		printf("enseash %% ");
		scanf("%s",typed_return);
		exit_command(typed_return);
		call_Command(typed_return);
	}
}



int main(){
	enseash();
	}
