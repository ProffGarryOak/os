#include <stdio.h>

int main() {
    int n, total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n], wt[n], tat[n], completion_time[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
    }

    // Sort processes by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                // Swap arrival times
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                // Swap burst times
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                // Swap process numbers
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    wt[0] = 0;
    completion_time[0] = arrival_time[0] + burst_time[0];
    tat[0] = burst_time[0];
    
    for (int i = 1; i < n; i++) {
        if (arrival_time[i] > completion_time[i - 1]) {
            completion_time[i] = arrival_time[i] + burst_time[i];
        } else {
            completion_time[i] = completion_time[i - 1] + burst_time[i];
        }
        wt[i] = completion_time[i] - arrival_time[i] - burst_time[i];
        if (wt[i] < 0) {
            wt[i] = 0;
        }
        tat[i] = burst_time[i] + wt[i];
    }

    printf("Processes  %-12s  %-12s  %-14s  %-16s  %-16s\n", "Arrival time", "Burst time", "Waiting time", "Turnaround time", "Completion time");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%-10d  %-12d  %-12d  %-14d  %-16d  %-16d\n", processes[i], arrival_time[i], burst_time[i], wt[i], tat[i], completion_time[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
