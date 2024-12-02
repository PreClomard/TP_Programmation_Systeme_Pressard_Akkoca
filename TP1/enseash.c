#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// In this code we print messages then
// wait for the user to type in order to exit
// the program

// On the terminal first type:
// 	gcc -o enseash enseash.c
//in order to compile it
//then type:
//	./enseash 
//to land the executable.

void enseash(){

	//Variable
	int comparString;

	//
	printf("Welcome to ENSEA Tiny SHell\n");
	printf("Type to exit\n");
	
	char typed_return[25];

	while(1){
		printf("enseash %% ");
		scanf("%s",typed_return);
		comparString=strcmp(typed_return,"exit");
		if(comparString == 0){
			exit(0);
		}	
	}
}

int main(){
	enseash();
	}
