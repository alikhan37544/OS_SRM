#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // For wait()

int main() {
    int pid, n, oddSum = 0, evenSum = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    pid = fork();
    if (pid == 0) {
        // Child process
        for (int i = 1; i <= n; i++) {
            if (i % 2 != 0) oddSum += i; // Sum of odd numbers
        }
        printf("Sum of odd numbers: %d\n", oddSum);
    } else {
        // Parent process waits for child to complete
        wait(NULL);
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) evenSum += i; // Sum of even numbers
        }
        printf("Sum of even numbers: %d\n", evenSum);
    }
    return 0;
}
