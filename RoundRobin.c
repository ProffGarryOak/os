#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, tq, current_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], remaining_time[n], arrival_time[n];
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    bool done[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        remaining_time[i] = burst_time[i];
        done[i] = false;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int completed = 0;
    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!done[i] && arrival_time[i] <= current_time) {
                found = true;
                if (remaining_time[i] > tq) {
                    current_time += tq;
                    remaining_time[i] -= tq;
                } else {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    wt[i] = current_time - burst_time[i] - arrival_time[i];
                    tat[i] = current_time - arrival_time[i];
                    total_wt += wt[i];
                    total_tat += tat[i];
                    done[i] = true;
                    completed++;
                }
            }
        }
        if (!found)
            current_time++;
    }

    printf("Processes  %-12s  %-12s  %-14s  %-16s\n", "Arrival time", "Burst time", "Waiting time", "Turnaround time");
    for (int i = 0; i < n; i++) {
        printf("%-10d  %-12d  %-12d  %-14d  %-16d\n", processes[i], arrival_time[i], burst_time[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
