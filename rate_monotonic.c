#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time; // in milliseconds
    int period; // in milliseconds
    int remaining_time; // in milliseconds
    int next_deadline; // in milliseconds
} Task;

void sortTasksByPeriod(Task tasks[], int num_tasks) {
    for (int i = 0; i < num_tasks - 1; ++i) {
        for (int j = 0; j < num_tasks - i - 1; ++j) {
            if (tasks[j].period > tasks[j + 1].period) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void simulateRMSScheduling(Task tasks[], int num_tasks, int hyper_period) {
    printf("Time(ms) | Task\n");
    printf("---------|-----\n");

    for (int time = 0; time < hyper_period; ++time) {
        int highest_priority_task = -1;
        for (int i = 0; i < num_tasks; ++i) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = time + tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 && (highest_priority_task == -1 || tasks[i].period < tasks[highest_priority_task].period)) {
                highest_priority_task = i;
            }
        }

        if (highest_priority_task != -1) {
            printf(" %7d |  T%d\n", time, tasks[highest_priority_task].id);
            tasks[highest_priority_task].remaining_time--;
        } else {
            printf(" %7d |  IDLE\n", time);
        }
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    if (num_tasks > MAX_TASKS) {
        printf("Maximum number of tasks exceeded!\n");
        return 1;
    }

    Task tasks[MAX_TASKS];
    int hyper_period = 1;

    for (int i = 0; i < num_tasks; ++i) {
        tasks[i].id = i + 1;
        printf("Enter execution time (ms) and period (ms) for Task %d: ", tasks[i].id);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].period);
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_deadline = tasks[i].period;

        hyper_period = lcm(hyper_period, tasks[i].period);
    }

    sortTasksByPeriod(tasks, num_tasks);
    simulateRMSScheduling(tasks, num_tasks, hyper_period);

    return 0;
}
