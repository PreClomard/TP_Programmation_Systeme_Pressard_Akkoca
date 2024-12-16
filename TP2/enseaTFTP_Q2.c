#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

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
 * Function: Get the addresse of the server
 */
void getaddr(const char *host){
    const char *domain_name = host;
    struct addrinfo hints, *res, *p;
    char ip_str[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;      
    hints.ai_socktype = SOCK_STREAM; 

    int status = getaddrinfo(domain_name, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    }

    printf("Addresses for %s:\n", domain_name);

    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        const char *ip_version;

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ip_version = "IPv4";
        } else if (p->ai_family == AF_INET6) { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ip_version = "IPv6";
        } else {
            continue;
        }

        inet_ntop(p->ai_family, addr, ip_str, sizeof(ip_str));
        printf("  %s: %s\n", ip_version, ip_str);
    }

    freeaddrinfo(res);
}

/**
 * Function: Launch every function
 * Variables:
 *      argv[1] indiccate wich function we will call
 *      argv[2] indicate the name of the server
 *      argv[3] indicate the name of the file
 */
int main(int argc, char *argv[]) {
    if ((argc !=3) & (argc !=4)) {
        fprintf(stderr, "Usage: %s <get|put> <host> <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "get") == 0) {
        gettftp(argv[2], argv[3]);
    } else if (strcmp(argv[1], "put") == 0) {
        puttftp(argv[2], argv[3]);
    } 
    else if (strcmp(argv[1],"getaddr")==0){
        getaddr(argv[2]);
    }else {
        fprintf(stderr, "Invalid command. Use 'get' or 'put'.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}