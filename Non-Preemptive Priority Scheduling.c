#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int arrival_time;
};

void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time || 
               (proc[i].arrival_time == proc[j].arrival_time && proc[i].priority > proc[j].priority)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
    }

    sortProcesses(proc, n);

    int wt[n], tat[n], total_wt = 0, total_tat = 0, current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
        wt[i] = current_time - proc[i].arrival_time;
        current_time += proc[i].burst_time;
        tat[i] = proc[i].burst_time + wt[i];
    }

    printf("Processes  %-12s  %-12s  %-12s  %-14s  %-16s\n", "Arrival time", "Burst time", "Priority", "Waiting time", "Turnaround time");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%-10d  %-12d  %-12d  %-12d  %-14d  %-16d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
