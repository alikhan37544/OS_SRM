#include <stdio.h>
#include <unistd.h>

int main() {
    fork(); // First fork call doubles the number of processes to 2
    fork(); // Second fork call doubles the number of processes again to 4
    fork(); // Third fork call doubles the number of processes once more to 8
    
    // At this point, there are 8 processes in total, each printing "SRMIST" once
    printf("SRMIST\n");

    return 0;
}

