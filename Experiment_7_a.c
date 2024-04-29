#include <stdio.h>

// Function to calculate average turnaround time and average waiting time
void calculateAvgTimes(int n, int bt[], int wt[], int tat[]) {
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

// Function to find waiting time for all processes
void findWaitingTime(int n, int bt[], int wt[]) {
    wt[0] = 0; // First process doesn't need to wait
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1]; // Waiting time is the sum of burst times of all previous processes
    }
}

// Function to find turnaround time for all processes
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time is burst time + waiting time
    }
}

// Function to find the average waiting time and turnaround time
void findAvgTimes(int n, int bt[]) {
    int wt[n], tat[n];

    // Find waiting time and turnaround time for all processes
    findWaitingTime(n, bt, wt);
    findTurnAroundTime(n, bt, wt, tat);

    // Calculate and print average waiting time and turnaround time
    calculateAvgTimes(n, bt, wt, tat);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n];
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Calculate average waiting time and turnaround time
    findAvgTimes(n, bt);

    return 0;
}

/*
Suppose we have nn processes with their burst times:

    First, we need to calculate the waiting time (WT) for each process. In FCFS, the waiting time for each process is the sum of the burst times of all preceding processes.
    Waiting Time (WT)i=∑j=0i−1Burst Timej
    Waiting Time (WT)i​=j=0∑i−1​Burst Timej​

    Then, we calculate the turnaround time (TAT) for each process. The turnaround time for each process is the sum of its burst time and waiting time.
    Turnaround Time (TAT)i=Burst Timei+Waiting Timei
    Turnaround Time (TAT)i​=Burst Timei​+Waiting Timei​

    Finally, we find the average waiting time and average turnaround time across all processes.
    Average Waiting Time (AWT)=∑Waiting Timein
    Average Waiting Time (AWT)=n∑Waiting Timei​​
    Average Turnaround Time (ATT)=∑Turnaround Timein
    Average Turnaround Time (ATT)=n∑Turnaround Timei​​

Let's illustrate these calculations with an example:

Suppose we have 3 processes with the following burst times:

    Process 1: Burst Time = 5
    Process 2: Burst Time = 3
    Process 3: Burst Time = 8

    Calculate Waiting Time (WT):
        WT(Process 1) = 0 (No previous process)
        WT(Process 2) = Burst Time(Process 1) = 5
        WT(Process 3) = Burst Time(Process 1) + Burst Time(Process 2) = 5 + 3 = 8

    Calculate Turnaround Time (TAT):
        TAT(Process 1) = Burst Time(Process 1) + Waiting Time(Process 1) = 5 + 0 = 5
        TAT(Process 2) = Burst Time(Process 2) + Waiting Time(Process 2) = 3 + 5 = 8
        TAT(Process 3) = Burst Time(Process 3) + Waiting Time(Process 3) = 8 + 8 = 16

    Calculate Average Waiting Time and Average Turnaround Time:
        AWT = (WT(Process 1) + WT(Process 2) + WT(Process 3)) / 3 = (0 + 5 + 8) / 3 = 13 / 3 ≈ 4.33
        ATT = (TAT(Process 1) + TAT(Process 2) + TAT(Process 3)) / 3 = (5 + 8 + 16) / 3 = 29 / 3 ≈ 9.67

So, in this example, the average waiting time is approximately 4.33 time units, and the average turnaround time is approximately 9.67 time units.
*/