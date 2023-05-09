/**
 * @file    NPP.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - NPP(Non-Preemption Prioity)
 *          - 
 *          - 
 * 
 * @version 0.1
 * @date    2023-05-10
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef NPP_H
#define NPP_H

Process result[5];

/**
 * @brief   compare function with qsort()
 * 
 * @param a compare target a
 * @param b compare target b
 * @return  int 
 */
int compare_for_NPP(const void* a, const void* b);

/**
 * @brief   Non-Preemption Prioity
 * 
 * @param p pointer for process struture
 * @param n process count
 */
void NPP(Process *p, int n) {
    
    double total_turnaround = 0;   
    double total_waiting    = 0;
    double total_response   = 0;

    // create ready queue & insert process to ready queue

    QueueType q;
    init_queue(&q);

    QueueType pre;
    init_queue(&pre);
    for(int i = 0; i < n; i++)
        ready_queue(&pre, p[i]);

    // running NPP scheduling

    Process *temp = NULL;
    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {
        
        if(!is_empty_q(&pre)) {
            if(check(&pre).arrival == time_flow) {
                ready_queue(&q, *dispatch(&pre));
                sort(&q, compare_for_NPP);
            }
        }
        
        // dispatch new PCB
        if(!is_empty_q(&q)) {
            if(check(&q).arrival <= time_flow && temp == NULL) {
                temp = dispatch(&q);
                temp->waiting = time_flow - temp->arrival;
                total_waiting += temp->waiting;
            }
        }

        time_flow++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;

            // terminate present PCB
            if(temp->remain == 0) {
                temp->turnaround    = temp->burst + temp->waiting;
                total_turnaround   += temp->turnaround;
                temp->response      = temp->waiting;
                total_response     += temp->response;
                result[terminate++] = *temp;
                temp = NULL;
            }
        }
    }
    //test print
    printf("\n\nNPP\n");
    printf("index\tPID\tArrival\tPrioity\tWaiting\tTurnaround\n");
    for(int i = 0; i < n; i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t\n", 
        i, 
        result[i].processID, 
        result[i].arrival, 
        result[i].prioity, 
        result[i].waiting,
        result[i].turnaround
        );
    printf("\ntime flow:\t\t%d\naverage turnaround:\t%.2lf\naverage waiting:\t%.2lf\naverage response:\t%.2lf", 
    time_flow, total_turnaround/n, total_waiting/n, total_response/n);
}

int compare_for_NPP(const void* a, const void* b) {
    
    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->prioity>B->prioity)-(A->prioity<B->prioity);
} 

#endif