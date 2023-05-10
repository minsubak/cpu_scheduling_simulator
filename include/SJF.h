/**
 * @file    SJF.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - SJF(Shortest Job First)
 *          - assign to CPU in order of burst time in the ready queue
 *          - improve efficiency by reducing the Conboy effect
 * 
 * @version 0.1
 * @date    2023-05-09
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef SJF_H
#define SJF_H

// standard library
#include <stdlib.h>

// external library & user define library
#include "queue.h"
#include "process.h"

/**
 * @brief SJF.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result           y           CPU scheduling result storage structure
 *  double      total_turnaround n           the sum of turnaround
 *  double      total_waiting    n           the sum of waiting
 *  double      total_response   n           the sum of response
 *  void        a                y           compare target variable a
 *  void        b                y           compare target variable b
 *  Process     A                y           compare target variable A(w. using void* a)
 *  Process     B                y           compare target variable B(w. using void* b)
 *  Process     p                y           pointer for process structure
 *  int         n                n           save process count
 *  QueueType   q                n           queue structure for queue(for ready queue)
 *  QueueType   pre              n           queue structure for queue(for previous queue)
 *  int         i                n           multipurpose utilization variable
 *  int         time_flow        n           flow of time in the scheduler
 *  int         terminate        n           Number of process terminated
 *  
 */

Process result[5];

/**
 * @brief   compare function with qsort
 * 
 * @param a compare target a
 * @param b compare target b
 * @return  int 
 */
int compare_for_SJF(const void* a, const void* b);

/**
 * @brief   Shortest Job First
 * 
 * @param p pointer for process struture
 * @param n process count
 */
void SJF(Process *p, int n) {
    
    double  total_turnaround = 0;   
    double  total_waiting    = 0;
    double  total_response   = 0;

    // create ready queue & insert process to ready queue

    QueueType q;
    init_queue(&q);

    QueueType pre;
    init_queue(&pre);
    for(int i = 0; i < n; i++)
        ready_queue(&pre, p[i]);

    // running SJF scheduling

    Process *temp = NULL;
    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {
        
        if(!is_empty_q(&pre)) {
            if(check(&pre).arrival == time_flow) {
                ready_queue(&q, *dispatch(&pre));
                sort(&q, compare_for_SJF);
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
    printf("\n\nSJF\n");
    printf("index\tPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i = 0; i < n; i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t\n", 
        i, 
        result[i].processID, 
        result[i].arrival, 
        result[i].burst, 
        result[i].waiting,
        result[i].turnaround
        );
    printf("\ntime flow:\t\t%d\naverage turnaround:\t%.2lf\naverage waiting:\t%.2lf\naverage response:\t%.2lf", 
    time_flow, total_turnaround/n, total_waiting/n, total_response/n);
}

int compare_for_SJF(const void* a, const void* b) {
    
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->burst>B->burst)-(A->burst<B->burst);
} 

#endif