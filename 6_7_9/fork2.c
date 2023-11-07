#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid, grandchild_pid;

    printf("Original parent process (PID: %d) : %d\n", getpid(), getppid());

    // First fork
    child_pid = fork();

    if (child_pid == 0) {
        // This block will be executed by the child process

        printf("First child process (PID: %d) : %d\n", getpid(), getppid());

        // Second fork inside the child process
        grandchild_pid = fork();

        if (grandchild_pid == 0) {
            // This block will be executed by the grandchild process

            printf("Second child process (PID: %d) : %d\n", getpid(), getppid());
            // Additional processing can be done in the grandchild process.

        } else if (grandchild_pid > 0) {
            // This block will be executed by the child process
            // Wait for the grandchild to finish
            wait(NULL);
        } else {
            // An error occurred during the second fork
            perror("Error in grandchild fork");
        }

        // Additional processing can be done in the child process.

    } else if (child_pid > 0) {
        // This block will be executed by the original parent process
        // Wait for the first child to finish
        wait(NULL);
    } else {
        // An error occurred during the first fork
        perror("Error in first child fork");
    }

    // Additional processing can be done in the original parent process.

    return 0;
}

