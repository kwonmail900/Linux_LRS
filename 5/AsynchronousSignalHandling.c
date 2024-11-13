#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigusr1_handler(int signum) {
    printf("Received SIGUSR1 signal asynchronously.\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error registering signal handler");
        return 1;
    }

    printf("Waiting for SIGUSR1 signal. Use 'kill -SIGUSR1 %d' to send the signal.\n", getpid());

    while (1) {
        // Perform some non-signal-related work
        sleep(1);
        printf("Doing some work...\n");
    }

    return 0;
}
