/**
 * @file    FCFS.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - FCFS(first come first served)
 *          - assign to CPU in order of arrival in the ready queue
 *          - once executed, wait until the next order is over
 *          - all processes have the same prioity
 * @version 0.1
 * @date    (first data: 2023-05-03)
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
#include "compare.h"

/**
 * @brief FCFS.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result           y           CPU scheduling result storage structure, external from "process.h"
 *  int         total_turnaround n           the sum of turnaround
 *  int         total_waiting    n           the sum of waiting
 *  int         total_response   n           the sum of response
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

extern Process result[MAX];

/**
 * @brief   First Come First Served
 * 
 * @param p pointer for process structer
 * @param n process count
 */
void FCFS(Process *p, int n) {
    
    int total_turnaround = 0;   
    int total_waiting    = 0;
    int total_response   = 0;
    int result_index     = 0;
    Process *temp     = NULL;

    // create queue & insert process to queue

    QueueType ready, pre;
    init_queue(&ready);
    init_queue(&pre);
    for(int i = 0; i < n; i++)
        timeout(&pre, p[i]);

    // sort by arrival
    sort(&pre, compare_for_arrival);
    
    // running FCFS scheduling

    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // number of process terminated
    while(terminate < n) {
        
        // insert prcoess into the ready queue in order of arrive
        if(!is_empty_q(&pre)) {
            if(check(&pre).arrival == time_flow) {
                timeout(&ready, *dispatch(&pre));
                printf("arrival:\tt: %d, p: %d\n", time_flow, ready.queue->processID);
            }
        }

        // dispatch new PCB: If the previous task terminated
        if(check(&ready).arrival <= time_flow && temp == NULL) {
            temp = dispatch(&ready);
            temp->waiting = time_flow - temp->arrival;
            total_waiting += temp->waiting;
            temp->execute = 0;
            printf("dispatch:\tt: %d, p: %d, w: %d\n", time_flow, temp->processID, temp->waiting);
        }

        time_flow++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;

            // terminate present PCB
            if(temp->remain == 0) {
                printf("terminate:\tt: %d, p: %d\n", time_flow, temp->processID);
                total_turnaround    += temp->execute + temp->waiting;
                total_response      += temp->waiting;
                result[result_index++] = *temp;
                temp = NULL;
                terminate++;
            }
        }
    }

    //test print
    printf("\n\nFCFS\n");
    printf("index\tPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i = 0; i < result_index; i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t\n", 
        i, 
        result[i].processID, 
        result[i].arrival, 
        result[i].burst, 
        result[i].waiting,
        (result[i].execute + result[i].waiting)
        );
    printf("\ntime flow:\t\t%d\naverage turnaround:\t%.1lf\naverage waiting:\t%.1lf\naverage response:\t%.1lf", 
    time_flow, (double)total_turnaround/n, (double)total_waiting/n, (double)total_response/n);
}

#endif