#include <stdio.h>

#define MAX 100

int main() {
    int n, tq1, tq2;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[MAX], bt[MAX], rt[MAX], ct[MAX], wt[MAX], tat[MAX];

    for(int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);

        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    printf("Enter Time Quantum 1: ");
    scanf("%d", &tq1);

    printf("Enter Time Quantum 2: ");
    scanf("%d", &tq2);

    int tq_arr[2] = {tq1, tq2};

    for(int t = 0; t < 2; t++) {
        int tq = tq_arr[t];

        for(int i = 0; i < n; i++) {
            rt[i] = bt[i];
            ct[i] = wt[i] = tat[i] = 0;
        }

        int queue[MAX], front = 0, rear = 0;
        int visited[MAX] = {0};

        int time = 0, completed = 0;

        while (1) {
            int found = 0;
            for(int i = 0; i < n; i++) {
                if(at[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    found = 1;
                }
            }
            if(found) break;
            time++;
        }

        while(front < rear) {
            int i = queue[front++];

            if(rt[i] > 0) {
                if(rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    completed++;
                } else {
                    time += tq;
                    rt[i] -= tq;
                }

                for(int j = 0; j < n; j++) {
                    if(at[j] <= time && visited[j] == 0) {
                        queue[rear++] = j;
                        visited[j] = 1;
                    }
                }

                if(rt[i] > 0) {
                    queue[rear++] = i;
                }
            }

            if(front == rear && completed < n) {
                for(int j = 0; j < n; j++) {
                    if(visited[j] == 0) {
                        time = at[j];
                        queue[rear++] = j;
                        visited[j] = 1;
                        break;
                    }
                }
            }
        }

        float total_wt = 0, total_tat = 0;

        printf("\n===== OUTPUT FOR TIME QUANTUM = %d =====\n", tq);
        printf("Process\tAT\tBT\tWT\tTAT\n");

        for(int i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);

            total_wt += wt[i];
            total_tat += tat[i];
        }

        printf("\nAverage Waiting Time = %.2f", total_wt/n);
        printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);
    }

    return 0;
}
