#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rem_bt;
};

int main(){
    int i, j, n, completed = 0, time = 0, tq;
    struct Process p[10];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    for (int i=0; i<n; i++){
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i+1;
        p[i].ct = 0;
        p[i].rem_bt = p[i].bt;
    }
    
    // //First Come First Serve Algo Logic 
    // for (int i=0; i<n-1; i++){
    //     for (int j=i+1; j<n; j++){
    //         if (p[i].at > p[j].at){
    //             struct Process temp = p[i];
    //             p[i] = p[j];
    //             p[j] = temp;
    //         }
    //     }
    // }
    
    // time = 0;
    // for(int i=0; i<n; i++){
    //     if (time < p[i].at) time = p[i].at;
    //     time += p[i].bt;
    //     p[i].ct = time;
    //     p[i].tat = p[i].ct - p[i].at;
    //     p[i].wt = p[i].tat - p[i].bt;
    // }
    
    //-----------------------------------------------------
    
    // //Shortest Job First Scheduling Algorithm
    // time = 0;
    // completed = 0;
    
    // while (completed != n){
    //     int min = 9999, pos = -1;
        
    //     for (int i=0; i<n; i++){
    //         if (p[i].at <= time && p[i].bt < min && p[i].ct == 0){
    //             min = p[i].bt;
    //             pos = i
    //         }
    //     }
        
    //     if (pos == -1){
    //         time++; 
    //         continue;
    //     }
        
    //     time += p[pos].bt;
    //     p[pos].ct = time;
    //     p[pos].tat = p[pos].ct - p[pos].at;
    //     p[pos].wt = p[pos].tat - p[pos].bt;
    //     completed++;
    //}
    
    //-------------------------------------------------------
    
    //Shortest Job Remaining First Algorithm
    //min -> min_rem and bt -> rem_bt
    // int prev = -1;
    // while (completed != n){
    //     int min_rem = 9999;
    //     int pos = -1;
        
    //     for (int i=0; i<n; i++){
    //         if (p[i].at <= time && p[i].rem_bt < min_rem && p[i].rem_bt > 0 ){
    //             min_rem = p[i].rem_bt;
    //             pos = i;
    //         }
    //     }
        
    //     if (pos == -1) {
    //         time++;
    //         continue;
    //     }
        
    //     p[pos].rem_bt--;
    //     time++;
        
    //     if (p[pos].rem_bt == 0){
    //         completed++;
    //         p[pos].ct = time;
    //         p[pos].tat = p[pos].ct - p[pos].at;
    //         p[pos].wt = p[pos].tat - p[pos].bt;
    //     }
    // }
    
    //--------------------------------------------------

    //Round Robin Scheduling Algorithm
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int rem = n;
    time = 0;

    while (rem > 0){
        int done_in_cycle = 0;
        for (int i=0; i<n; i++){
            if (p[i].at <= time && p[i].rem_bt > 0){
                done_in_cycle = 1;

                if (p[i].rem_bt > tq){
                    time += tq;
                    p[i].rem_bt -= tq;
                }
                else {
                    time += p[i].rem_bt;
                    p[i].rem_bt = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    rem--;
                }
            }
        }
        if (!done_in_cycle) time++;
    }
    
    
    
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n; i++){
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    float tot_tat = 0, tot_wt = 0;
    for (int i=0; i<n; i++){
        tot_tat += p[i].tat;
        tot_wt += p[i].wt;
    }
    printf ("Average TAT: %.2f\n", tot_tat/n);
    printf ("Average WT: %.2f\n", tot_wt/n);
    
    return 0;
}