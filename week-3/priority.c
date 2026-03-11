#include <stdio.h>

#define MAX 20

// Non-Preemptive Priority Scheduling
void nonPreemptive(int n, int at[], int bt[], int pr[]) {
    int completed[MAX] = {0};
    int wt[MAX] = {0}, tat[MAX] = {0};
    int time = 0, done = 0;

    printf("\n--- Non Preemptive Priority Scheduling ---\n");

    while(done < n) {
        int idx = -1;
        int highest = 9999;

        // Find highest priority process that has arrived
        for(int i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(pr[i] < highest) {
                    highest = pr[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++; // CPU idle
            continue;
        }

        time += bt[idx];

        tat[idx] = time - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        completed[idx] = 1;
        done++;
    }

    float avgWT = 0, avgTAT = 0;

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], wt[i], tat[i]);

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);
}


// Preemptive Priority Scheduling
void preemptive(int n, int at[], int bt[], int pr[]) {

    int remaining[MAX];
    int wt[MAX] = {0}, tat[MAX] = {0};
    int complete = 0, time = 0;

    for(int i = 0; i < n; i++)
        remaining[i] = bt[i];

    printf("\n--- Preemptive Priority Scheduling ---\n");

    while(complete < n) {

        int idx = -1;
        int highest = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && remaining[i] > 0) {
                if(pr[i] < highest) {
                    highest = pr[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        remaining[idx]--;
        time++;

        if(remaining[idx] == 0) {
            complete++;

            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        }
    }

    float avgWT = 0, avgTAT = 0;

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], wt[i], tat[i]);

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);
}


int main() {

    int n;
    int at[MAX], bt[MAX], pr[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Ask inputs separately
    for(int i = 0; i < n; i++) {

        printf("\nProcess %d\n", i+1);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Enter Priority: ");
        scanf("%d", &pr[i]);
    }

    // Run both algorithms
    nonPreemptive(n, at, bt, pr);
    preemptive(n, at, bt, pr);

    return 0;
}
