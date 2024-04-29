#include <stdio.h>
#include <unistd.h>

int main() {
    fork(); // First doubling: 2 processes
    fork() && fork() || fork(); // Complex expression causing more forks
    fork(); // Last doubling: increases the total number of processes significantly
    
    printf("Yes\n");
    return 0;
}
