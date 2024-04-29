#include <stdio.h>

// Function to calculate average turnaround time and average waiting time
void calculateAvgTimes(int n, int wt[], int tat[]) {
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

// Function to find waiting time for all processes
void findWaitingTime(int n, int bt[], int wt[], int priority[]) {
    wt[0] = 0; // First process doesn't need to wait

    // Calculate waiting time for remaining processes
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1]; // Waiting time is the sum of burst times of all previous processes
    }
}

// Function to find turnaround time for all processes
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time is burst time + waiting time
    }
}

// Function to find the process with the highest priority
int findHighestPriorityProcess(int n, int priority[], int processed[]) {
    int maxPriority = -1, maxPriorityProcess = -1;
    for (int i = 0; i < n; i++) {
        if (!processed[i] && priority[i] > maxPriority) {
            maxPriority = priority[i];
            maxPriorityProcess = i;
        }
    }
    return maxPriorityProcess;
}

// Function to find the average waiting time and turnaround time
void findAvgTimes(int n, int bt[], int priority[]) {
    int wt[n], tat[n];
    int processed[n]; // Define processed array separately

    // Initialize processed array to all zeros
    for (int i = 0; i < n; i++) {
        processed[i] = 0;
    }

    // Find waiting time and turnaround time for all processes
    findWaitingTime(n, bt, wt, priority);
    findTurnAroundTime(n, bt, wt, tat);

    // Calculate and print average waiting time and turnaround time
    calculateAvgTimes(n, wt, tat);
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], priority[n];
    printf("Enter burst times and priorities for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Calculate average waiting time and turnaround time
    findAvgTimes(n, bt, priority);

    return 0;
}
