#include <stdio.h>

int main() {
    int n, i, time, remain, tq1, tq2;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n], completed[n];

    // Input Arrival and Burst Time
    for(i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);

        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    // Time quantums
    printf("Enter Time Quantum 1: ");
    scanf("%d", &tq1);

    printf("Enter Time Quantum 2: ");
    scanf("%d", &tq2);

    int tq_arr[2] = {tq1, tq2};

    for(int k = 0; k < 2; k++) {
        int tq = tq_arr[k];

        printf("\n===== OUTPUT FOR TIME QUANTUM = %d =====\n", tq);

        // Reset values
        time = 0;
        remain = n;

        for(i = 0; i < n; i++) {
            rt[i] = bt[i];
            wt[i] = 0;
            tat[i] = 0;
            completed[i] = 0;
        }

        while(remain > 0) {
            int executed = 0;

            for(i = 0; i < n; i++) {
                if(at[i] <= time && rt[i] > 0) {

                    executed = 1;

                    if(rt[i] <= tq) {
                        time += rt[i];
                        rt[i] = 0;
                        tat[i] = time - at[i];
                        wt[i] = tat[i] - bt[i];
                        completed[i] = 1;
                        remain--;
                    } else {
                        time += tq;
                        rt[i] -= tq;
                    }
                }
            }

            // If no process is ready, move time forward
            if(executed == 0) {
                time++;
            }
        }

        // Print results
        float total_wt = 0, total_tat = 0;

        printf("\nProcess\tAT\tBT\tWT\tTAT\n");
        for(i = 0; i < n; i++) {
            printf("P%d\t%d\t%d\t%d\t%d\n",
                   i + 1, at[i], bt[i], wt[i], tat[i]);

            total_wt += wt[i];
            total_tat += tat[i];
        }

        printf("\nAverage Waiting Time = %.2f", total_wt / n);
        printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    }

    return 0;
}
