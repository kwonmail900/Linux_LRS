#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigusr1_handler(int signum, siginfo_t* info, void* context) {
    printf("Received SIGUSR1 signal with value: %d\n", info->si_value.sival_int);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO; // Use extended signal handling with siginfo_t
    sa.sa_sigaction = sigusr1_handler;

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error registering signal handler");
        return 1;
    }

    // Sending SIGUSR1 signal with a value (e.g., 42)
    union sigval value;
    value.sival_int = 42;
    if (sigqueue(getpid(), SIGUSR1, value) == -1) {
        perror("Error sending signal");
        return 1;
    }

    printf("SIGUSR1 signal sent with value: %d\n", value.sival_int);

    return 0;
}

