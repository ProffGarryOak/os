#include <stdio.h>

int main() {
    int n, tq, current_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], remaining_time[n], wt[n], tat[n], total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] > tq) {
                    current_time += tq;
                    remaining_time[i] -= tq;
                } else {
                    current_time += remaining_time[i];
                    wt[i] = current_time - burst_time[i];
                    remaining_time[i] = 0;
                    tat[i] = wt[i] + burst_time[i];
                    total_wt += wt[i];
                    total_tat += tat[i];
                    completed++;
                }
            }
        }
    }

    printf("Processes  %-12s  %-14s  %-16s\n", "Burst time", "Waiting time", "Turnaround time");
    for (int i = 0; i < n; i++) {
        printf("%-10d  %-12d  %-14d  %-16d\n", processes[i], burst_time[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
