#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

// Signal handler function
void sigio_handler(int signum) {
    printf("Data is available to read.\n");
}

int main() {
    int fd;
    char buffer[256];

    // Open a file in read-only mode
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Set the file descriptor to be signal-driven
    if (fcntl(fd, F_SETOWN, getpid()) == -1) {
        perror("Error setting process as the owner");
        close(fd);
        return 1;
    }

    // Enable the FASYNC flag to enable signal-driven I/O
    if (fcntl(fd, F_SETFL, O_ASYNC) == -1) {
        perror("Error enabling signal-driven I/O");
        close(fd);
        return 1;
    }

    // Register the signal handler for SIGIO (or SIGPOLL)
    signal(SIGIO, sigio_handler);

    printf("Waiting for data to be available in the file...\n");
    while (1) {
        // Do other work or sleep here
        sleep(1);
    }

    close(fd);
    return 0;
}

