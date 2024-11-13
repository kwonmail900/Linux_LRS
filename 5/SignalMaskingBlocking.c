#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigint_handler(int signum) {
    printf("\nReceived SIGINT signal. Press 'q' to quit.\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error registering signal handler");
        return 1;
    }

    // Block SIGINT signal
    sigset_t new_mask, old_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        perror("Error blocking SIGINT");
        return 1;
    }

    printf("SIGINT is blocked. Press 'q' to unblock and quit.\n");

    // Wait for the user to input 'q' to unblock the signal and quit
    char input;
    do {
        input = getchar();
    } while (input != 'q');

    // Restore the old signal mask (unblock SIGINT)
    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        perror("Error restoring signal mask");
        return 1;
    }

    printf("SIGINT is unblocked. Exiting the program.\n");

    return 0;
}

