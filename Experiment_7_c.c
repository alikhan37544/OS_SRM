#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 10

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
void findWaitingTime(int n, int bt[], int wt[], int rt[]) {
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int flag = 0;

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((rt[j] > 0) && (rt[j] < minm) && (t >= bt[j])) {
                minm = rt[j];
                shortest = j;
                flag = 1;
            }
        }

        if (flag == 0) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0) {
            minm = INT_MAX;
        }

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            complete++;
            flag = 0;
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - bt[shortest];

            if (wt[shortest] < 0) {
                wt[shortest] = 0;
            }
        }

        // Increment time
        t++;
    }
}

// Function to find turnaround time for all processes
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to find the average waiting time and turnaround time
void findAvgTimes(int n, int bt[]) {
    int wt[n], tat[n], rt[n];

    // Find waiting time for all processes
    findWaitingTime(n, bt, wt, rt);

    // Find turnaround time for all processes
    findTurnAroundTime(n, bt, wt, tat);

    // Calculate and print average waiting time and turnaround time
    calculateAvgTimes(n, wt, tat);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    int bt[MAX_PROCESSES];
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Calculate average waiting time and turnaround time
    findAvgTimes(n, bt);

    return 0;
}
