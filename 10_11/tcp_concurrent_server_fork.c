#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void handle_client(int client_socket, int n) {
    char buffer[BUFFER_SIZE];
    int i;

    for (i = 0; i < n; i++) {
        snprintf(buffer, BUFFER_SIZE, "Reply %d from server.", i + 1);
        send(client_socket, buffer, strlen(buffer), 0);
        sleep(1); // A small delay to demonstrate the server sending multiple replies
    }

    close(client_socket);
    exit(EXIT_SUCCESS);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int n;

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080...\n");

    while (1) {
        // Accept the client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        // Fork a child process to handle the client connection
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            close(client_socket);
            continue;
        } else if (pid == 0) {
            // Child process
            close(server_socket); // Child doesn't need the listening socket
            recv(client_socket, &n, sizeof(n), 0); // Receive the value of n from the client
            handle_client(client_socket, n); // Handle the client's request
            exit(EXIT_SUCCESS); // Child process exits after handling the client
        } else {
            // Parent process
            close(client_socket); // Parent doesn't need the connected socket
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}

