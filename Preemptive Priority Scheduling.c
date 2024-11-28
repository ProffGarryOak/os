#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int remaining_time;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &proc[i].burst_time, &proc[i].priority);
        proc[i].remaining_time = proc[i].burst_time;
    }

    int completed = 0, current_time = 0, min_priority = INT_MAX, shortest = 0;
    int finish_time;
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if ((proc[i].remaining_time > 0) && (proc[i].priority < min_priority)) {
                min_priority = proc[i].priority;
                shortest = i;
            }
        }

        proc[shortest].remaining_time--;
        min_priority = INT_MAX;

        if (proc[shortest].remaining_time == 0) {
            completed++;
            finish_time = current_time + 1;
            wt[shortest] = finish_time - proc[shortest].burst_time;
            tat[shortest] = finish_time;
        }
        current_time++;
    }

    printf("Processes  %-12s  %-12s  %-14s  %-16s\n", "Burst time", "Priority", "Waiting time", "Turnaround time");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%-10d  %-12d  %-12d  %-14d  %-16d\n", proc[i].pid, proc[i].burst_time, proc[i].priority, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
