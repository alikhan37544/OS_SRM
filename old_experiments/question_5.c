#include <stdio.h>
#include <unistd.h>

int main() {
    int n, i;
    printf("Enter the number of fork() calls: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        if(fork() == 0) {
            // Child process
            printf("Child PID: %d from Parent PID: %d\n", getpid(), getppid());
            // Exit the child process to prevent it from continuing the loop and creating more processes
            _exit(0);
        }
        // Parent process waits for the child to prevent zombie processes
        wait(NULL);
    }

    return 0;
}
