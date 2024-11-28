#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], wt[n], tat[n], total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burst_time[i] > burst_time[j]) {
                int temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = burst_time[i - 1] + wt[i - 1];

    for (int i = 0; i < n; i++)
        tat[i] = burst_time[i] + wt[i];

    printf("Processes  %-12s  %-14s  %-16s\n", "Burst time", "Waiting time", "Turnaround time");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%-10d  %-12d  %-14d  %-16d\n", processes[i], burst_time[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
