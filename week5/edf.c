#include <stdio.h>

struct Process {
    int id;
    int at, bt, deadline;
    int remaining;
    int completed;
};

int main() {
    int n, i, t = 0, completed = 0;
    float U = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline: ");
        scanf("%d", &p[i].deadline);

        p[i].id = i + 1;
        p[i].remaining = p[i].bt;
        p[i].completed = 0;

        U += (float)p[i].bt / p[i].deadline;
    }

    printf("\nCPU Utilization = %.2f\n", U);

    if(U > 1) {
        printf("Scheduling NOT feasible (deadlines may be missed)\n");
    } else {
        printf("Scheduling feasible\n");
    }

    printf("\nExecution Order:\n");

    while(completed < n) {
        int idx = -1;
        int min_deadline = 9999;

        for(i = 0; i < n; i++) {
            if(p[i].at <= t && p[i].completed == 0) {
                if(p[i].deadline < min_deadline) {
                    min_deadline = p[i].deadline;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            t++;
            continue;
        }

        printf("Time %d -> P%d\n", t, p[idx].id);

        p[idx].remaining--;

        if(p[idx].remaining == 0) {
            p[idx].completed = 1;
            completed++;
        }

        t++;
    }

    printf("\nAll processes completed.\n");

    return 0;
}
