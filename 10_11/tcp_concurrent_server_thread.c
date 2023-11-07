#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

struct ClientData {
    int client_socket;
    int n;
};

void *handle_client(void *arg) {
    struct ClientData *data = (struct ClientData *)arg;
    char buffer[BUFFER_SIZE];
    int i;

    for (i = 0; i < data->n; i++) {
        snprintf(buffer, BUFFER_SIZE, "Reply %d from server.", i + 1);
        send(data->client_socket, buffer, strlen(buffer), 0);
        sleep(1); // A small delay to demonstrate the server sending multiple replies
    }

    close(data->client_socket);
    free(data);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t thread;
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

        // Get the value of n from the client
        recv(client_socket, &n, sizeof(n), 0);

        // Create a new thread to handle the client connection
        struct ClientData *data = (struct ClientData *)malloc(sizeof(struct ClientData));
        data->client_socket = client_socket;
        data->n = n;

        if (pthread_create(&thread, NULL, handle_client, data) != 0) {
            perror("Thread creation failed");
            close(client_socket);
            free(data);
            continue;
        }

        // Detach the thread so that it can clean up after itself
        pthread_detach(thread);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}

