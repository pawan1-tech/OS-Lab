#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];  // pipe file descriptors
    char message[BUFFER_SIZE];

    // Create a pipe for communication between parent and child
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close read end of the pipe

        printf("Enter message to send to child: ");
        fgets(message, BUFFER_SIZE, stdin);

        // Write message to the pipe
        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]); // Close write end of the pipe
    } else { // Child process
        close(pipefd[1]); // Close write end of the pipe

        // Read message from the pipe
        read(pipefd[0], message, BUFFER_SIZE);
        printf("Child received message: %s", message);

        close(pipefd[0]); // Close read end of the pipe
    }

    return 0;
}
