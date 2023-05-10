/**
 * @file    FCFS.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - FCFS(first come first served)
 *          - assign to CPU in order of arrival in the ready queue
 *          - once executed, wait until the next order is over
 *          - all processes have the same prioity
 * @version 0.1
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef FCFS_H
#define FCFS_H

// standard library
#include <stdlib.h>

// external library & user define library
#include "queue.h"
#include "process.h"

/**
 * @brief FCFS.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result_fcfs      y           CPU scheduling result_fcfs storage structure
 *  double      total_turnaround n           the sum of turnaround
 *  double      total_waiting    n           the sum of waiting
 *  double      total_response   n           the sum of response
 *  Process     p                y           structure for process data storage
 *  int         n                n           save process count
 *  Process     temp             y           pointer of process structure temporary variable
 *  int         i                n           multipurpose utilization variable
 *  int         j                n           multipurpose utilization variable
 *  QueueType   ready            n           structure for Queue structure and data storage
 *  int         time_flow        n           flow of time in the scheduler
 *  int         terminate        n           Number of process terminated
 *  
 */

Process result_fcfs[5];

/**
 * @brief   First Come First Served
 * 
 * @param p pointer for process structer
 * @param n process count
 */
void FCFS(Process *p, int n) {
    
    double  total_turnaround = 0;   
    double  total_waiting    = 0;
    double  total_response   = 0;

    // sort by arrival

    Process *temp = NULL;
    for(int i = 0; i < n; i ++)
        for(int j = 0 ; j < i; j++)
            if(p[i].arrival < p[j].arrival) {
                *temp = p[i];
                p[i]  = p[j];
                p[j]  = *temp;
            }

    // create ready queue & insert process to ready queue

    QueueType ready;
    init_queue(&ready);
    for(int i = 0; i < n; i++)
        timeout(&ready, p[i]);
    
    // running FCFS scheduling

    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {
        
        // dispatch new PCB
        if(check(&ready).arrival <= time_flow && temp == NULL) {
            temp = dispatch(&ready);
            temp->waiting = time_flow - temp->arrival;
            total_waiting += temp->waiting;
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
                result_fcfs[terminate++] = *temp;
                temp = NULL;
            }
        }
    }

    //test print
    printf("\n\nFCFS\n");
    printf("index\tPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i = 0; i < n; i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t\n", 
        i, 
        result_fcfs[i].processID, 
        result_fcfs[i].arrival, 
        result_fcfs[i].burst, 
        result_fcfs[i].waiting,
        result_fcfs[i].turnaround
        );
    printf("\ntime flow:\t\t%d\naverage turnaround:\t%.2lf\naverage waiting:\t%.2lf\naverage response:\t%.2lf", 
    time_flow, total_turnaround/n, total_waiting/n, total_response/n);
}

#endif