#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Function: Get a file from the server
 */
void gettftp(const char *host, const char *filename) {
    char prompt[100];
    snprintf(prompt, sizeof(prompt), "Getting file '%s' from server '%s'\n", filename, host);
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * Function: Put a file in the server
 */
void puttftp(const char *host, const char *filename) {
    char prompt[100];
    snprintf(prompt, sizeof(prompt), "Putting file '%s' to server '%s'\n", filename, host);
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * Function: Launch every function
 * Variables:
 *      argv[1] indiccate wich function we will call
 *      argv[2] indicate the name of the server
 *      argv[3] indicate the name of the file
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <get|put> <host> <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "get") == 0) {
        gettftp(argv[2], argv[3]);
    } else if (strcmp(argv[1], "put") == 0) {
        puttftp(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Invalid command. Use 'get' or 'put'.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}