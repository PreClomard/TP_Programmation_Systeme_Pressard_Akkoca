#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
*	Function to create the micro shell
*/
void enseash(){
	//Variables
	const char *welcome_message = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n";
    char prompt[25] = "enseash %% ";

    //Write in the terminal the welcom message
	write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
	write(STDOUT_FILENO, prompt , strlen(prompt ));
}



int main(){
	enseash();
	}
