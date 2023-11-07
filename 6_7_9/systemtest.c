#include <stdlib.h>

int main() {
    int status = system("ls -l");
    if (status == -1) {
        // Failed to execute the command
        // Handle the error
    } else if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        // Command executed successfully
        // Process exit_status
    } else if (WIFSIGNALED(status)) {
        int signal_number = WTERMSIG(status);
        // Command terminated by a signal
        // Process signal_number
    }
    return 0;
}



