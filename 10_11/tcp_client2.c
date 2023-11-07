#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int n, i;

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Get the value of n from the user
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Send the value of n to the server
    send(client_socket, &n, sizeof(n), 0);

    // Receive and print the reply message n times from the server
    for (i = 0; i < n; i++) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            perror("Receive failed");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
        buffer[bytes_received] = '\0';
        printf("Reply %d from server: %s\n", i + 1, buffer);
    }

    // Close the socket
    close(client_socket);

    return 0;
}

