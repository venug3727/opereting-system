#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void priorityNonPreemptiveScheduling(struct Process processes[], int n) {
    int time = 0;
    int remaining_processes = n;

    while (remaining_processes > 0) {
        int highest_priority_index = -1;
        int highest_priority = -1;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].completion_time == 0) {
                if (highest_priority_index == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        // If no process is found, move time to next arrival
        if (highest_priority_index == -1) {
            int next_arrival = __INT_MAX__;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time < next_arrival && processes[i].completion_time == 0) {
                    next_arrival = processes[i].arrival_time;
                }
            }
            time = next_arrival;
        } else {
            // Execute the process
            processes[highest_priority_index].completion_time = time + processes[highest_priority_index].burst_time;
            time += processes[highest_priority_index].burst_time;
            remaining_processes--;
        }
    }

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    priorityNonPreemptiveScheduling(processes, n);

    // Output process details
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }

    return 0;
}
