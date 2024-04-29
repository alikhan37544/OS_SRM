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
    int rt[n];
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i]; // Copy burst time to remaining time
    }
    int complete = 0, t = 0, min_bt = 9999, shortest = 0, finish_time;

    while (complete != n) {
        // Find process with minimum remaining time at current time
        for (int j = 0; j < n; j++) {
            if ((rt[j] < min_bt) && (rt[j] > 0) && (t >= bt[j])) {
                min_bt = rt[j];
                shortest = j;
            }
        }

        // Decrease remaining time for the chosen process
        rt[shortest]--;

        // Update minimum remaining time
        min_bt = rt[shortest];
        if (min_bt == 0) {
            min_bt = 9999; // Set min_bt to a large value to find the next shortest process
        }

        // If process is finished
        if (rt[shortest] == 0) {
            complete++;
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - bt[shortest];

            if (wt[shortest] < 0) {
                wt[shortest] = 0; // Set waiting time to 0 if it's negative
            }
        }

        t++; // Increment time
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
