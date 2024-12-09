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
	char prompt[50];
  
	pid_t pid = fork();
	if (pid == 0) { // Child process
		char *args[] = {input, NULL};
		execvp(args[0], args);
		const char *error_message = "Command not found\n";
		write(STDOUT_FILENO, error_message, strlen(error_message));
		_exit(1);
	} else if (pid > 0) { // Parent process
		
		int status;
		
		//pid_t fpid;
		waitpid(pid, &status, 0);		
       
		// Update the prompt based on the child process status
		if (WIFEXITED(status)) {
			snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %%", WEXITSTATUS(status));
			write(STDOUT_FILENO, prompt, strlen(prompt));
		} else if (WIFSIGNALED(status)) {
			snprintf(prompt, sizeof(prompt), "ensea [sign:%d] %%", WTERMSIG(status));
			write(STDOUT_FILENO, prompt, strlen(prompt));
		}
		else if (status == -1 ) {
			snprintf(prompt, sizeof(prompt), "enseash %% ");
			write(STDOUT_FILENO, prompt, strlen(prompt));
		} 
		
		
	} else {
		const char *error_message = "Fork failed\n";
		write(STDOUT_FILENO, error_message, strlen(error_message));
	}
}

/*
*	Exit the micro shell
*
*	To do it we want to have the command exit or if we have a length of 0
*	because the size 0 mean that there was nothing more to read
*/
void exit_command(char command[25],ssize_t length){
	//Variables
	const char *bye_message = "\nBye bye...\n";
	int comparString;

	comparString=strcmp(command,"exit");

	if(comparString == 0 || length ==0){
		write(STDOUT_FILENO, bye_message, strlen(bye_message));
		exit(0);
	}
}


/*
*	Function to create the micro shell
*/
void enseash(){
	//Variables
	const char *welcome_message = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n enseash %%";
	char typed_return[25];


	//Write in the terminal the welcom message
	write(STDOUT_FILENO, welcome_message, strlen(welcome_message));

	//We want to prompt enseash % after call a function like date
	for(int i=0;i<6;i++){

		ssize_t length = read(STDIN_FILENO, typed_return, sizeof(typed_return) - 1);
		typed_return[length - 1] = '\0';
		exit_command(typed_return,length);
		if(length>0){
			call_Command(typed_return);
		}
	}
}



int main(){
	enseash();
	}
