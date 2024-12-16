#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define TFTP_PORT 69
#define RRQ 1
#define WRQ 2
#define DATA 3
#define ACK 4
#define ERROR 5

typedef struct {
    uint16_t opcode;
    char filename[256];
    char mode[8];
} tftp_rrq_t;

typedef struct {
    uint16_t opcode;
    char filename[256];
    char mode[8];
} tftp_wrq_t;

typedef struct {
    uint16_t opcode;
    uint16_t block_num;
    char data[512];
} tftp_data_t;

typedef struct {
    uint16_t opcode;
    uint16_t block_num;
} tftp_ack_t;

void gettftp(const char *host, const char *filename) {
    int sockfd;
    struct sockaddr_in server_addr;
    tftp_rrq_t rrq;
    ssize_t n;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[512];

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TFTP_PORT);
    inet_pton(AF_INET, host, &server_addr.sin_addr);

    // Prepare RRQ packet
    rrq.opcode = htons(RRQ);
    strcpy(rrq.filename, filename);
    strcpy(rrq.mode, "octet");
    
    // Send RRQ
    sendto(sockfd, &rrq, sizeof(rrq) + strlen(rrq.filename) + strlen(rrq.mode) + 2, 0, 
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Receive data
    int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file < 0) {
        perror("open");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
        if (n < 0) {
            perror("recvfrom");
            break;
        }

        // Handle DATA packet
        tftp_data_t *data_packet = (tftp_data_t *)buffer;
        uint16_t block_num = ntohs(data_packet->block_num);
        
        if (data_packet->opcode == ntohs(DATA)) {
            write(file, data_packet->data, n - 4); // Exclude opcode and block number
            tftp_ack_t ack;
            ack.opcode = htons(ACK);
            ack.block_num = htons(block_num);
            sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&server_addr, addr_len);
        }

        // Break on the last DATA packet (with less than 512 bytes)
        if (n < 516) break; 
    }

    close(file);
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <get|put> <host> <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "get") == 0) {
        gettftp(argv[2], argv[3]);
    }else {
        fprintf(stderr, "Invalid command. Use 'get' or 'put'.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}