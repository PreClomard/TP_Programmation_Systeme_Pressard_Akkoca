#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

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
void call_Command(char input[25]){
	pid_t pid = fork();
	if (pid == 0) { // Child process
		char *args[] = {input, NULL};
		execvp(args[0], args);
		const char *error_message = "Command not found\n";
		write(STDOUT_FILENO, error_message, strlen(error_message));
		_exit(1);
	} else if (pid > 0) { // Parent process
		int status;
		waitpid(pid, &status, 0);
	} else {
		const char *error_message = "Fork failed\n";
		write(STDOUT_FILENO, error_message, strlen(error_message));
	}
}

/*
*	Exit the micro shell
*/
void exit_command(char command[25]){
	const char *bye_message = "Bye bye...\n";
	int comparString;

	comparString=strcmp(command,"exit");
	if(comparString == 0){
		write(STDOUT_FILENO, bye_message, strlen(bye_message));
		exit(0);
	}	
}


/*
*	Function to create the micro shell
*/
void enseash(){
	const char *welcome_message = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n";
    const char *prompt = "enseash %% ";
	const char *exit_shell = "Type 'exit' to quit\n";

	write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
	write(STDOUT_FILENO, exit_shell , strlen(exit_shell));
	
	
	char typed_return[25];

	for(int i=0;i<6;i++){
		
		write(STDOUT_FILENO, prompt , strlen(prompt ));
		ssize_t length = read(STDIN_FILENO, typed_return, sizeof(typed_return) - 1);
		if(length>0){
			typed_return[length - 1] = '\0';
			exit_command(typed_return);
			call_Command(typed_return);
		}
		
	}
}



int main(){
	enseash();
	}
