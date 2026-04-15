#include <stdio.h>

#define MAX 20

struct Process {
    int id;
    int burst;
    int weight;
    int remaining;
};

int main() {
    int n, i, t = 0, completed = 0;
    int total_weight = 0;
    int TIME_QUANTUM = 10;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX];

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Weight: ");
        scanf("%d", &p[i].weight);

        p[i].id = i + 1;
        p[i].remaining = p[i].burst;

        total_weight += p[i].weight;
    }

    printf("\nExecution Order:\n");

    // Scheduling loop
    while(completed < n) {
        for(i = 0; i < n; i++) {

            if(p[i].remaining > 0) {

                // time_slice = (weight / total_weight) * TIME_QUANTUM
                int time_slice = (p[i].weight * TIME_QUANTUM) / total_weight;

                if(time_slice == 0)
                    time_slice = 1;

                if(time_slice > p[i].remaining)
                    time_slice = p[i].remaining;

                printf("P%d runs from %d to %d\n", p[i].id, t, t + time_slice);

                t += time_slice;
                p[i].remaining -= time_slice;

                // if completed
                if(p[i].remaining == 0) {
                    completed++;
                    total_weight -= p[i].weight;
                }
            }
        }
    }

    printf("\nAll processes completed.\n");

    return 0;
}
