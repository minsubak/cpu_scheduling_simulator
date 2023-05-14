/**
 * @file   _rr.h
 * @author  your name (minsu5875@naver.com)
 * @brief   rrCPU schedule simulator
 *          = non preemeption method - RR(Round-Robin)
 *          - 
 *          - 
 * 
 * @version 0.1
 * @date    2023-05-13
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef RR_H
#define RR_H

// standard library
#include <stdlib.h>

// external library & user define library
#include "queue.h"
#include "process.h"

/**
 * @brief RR.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result           y           CPU scheduling result storage structure
 *  double      total_turnaround n           the sum of turnaround
 *  double      total_waiting    n           the sum of waiting
 *  double      total_response   n           the sum of response
 *  Process     p                y           structure for process data storage
 *  int         n                n           save process count
 *  int         t                n           save time slice value
 *  
 */

extern Process result[MAX];

int compare_for_RR(const void* a, const void* b);

/**
 * @brief   Round-Robin
 * 
 * @param p pointer for process struture
 * @param n process count
 * @param t variable of time slice
 */
void RR(Process *p, int n, int t) {
    
    double  total_turnaround = 0;   
    double  total_waiting    = 0;
    double  total_response   = 0;
    int     result_index     = 0;

    Process *temp = NULL;

    // create ready queue & insert process to ready queue

    QueueType ready;
    init_queue(&ready);
    for(int i = 0; i < n; i++)
        timeout(&ready, p[i]);
    
    // sort by arrival
    sort(&ready, compare_for_RR);
    
    // running RR scheduling

    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {

        // dispatch new PCB and time-out present PCB
        if(!is_empty_q(&ready)) {
            if(check(&ready).arrival <= time_flow && temp == NULL) {
                temp = dispatch(&ready);
                printf("dispatch - t: %d p: %d w: %d\n", time_flow, temp->processID, temp->waiting);
                temp->waiting = time_flow - temp->timeout;
                total_waiting += temp->waiting;
                temp->execute = 0;
            }
        }

        // check prioity value during operation
        if(!is_empty_q(&ready)) {
            if(time_flow/t == 0 && time_flow != 0) {
                temp->timeout = time_flow;
                printf("timeout! - t: %d p: %d\n", time_flow, temp->processID);
                temp->turnaround    = temp->execute + temp->waiting;
                total_turnaround   += temp->turnaround;
                temp->response      = temp->waiting;
                total_response     += temp->response;
                result[result_index].execute = temp->execute;
                result[result_index++] = *temp;
                timeout(&ready, *temp);
                temp = dispatch(&ready);
            }            
        }

        time_flow++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;

            // terminate present PCB
            if(temp->remain == 0) {
                printf("terminate! - t: %d p: %d\n", time_flow, temp->processID);
                temp->turnaround    = temp->execute + temp->waiting;
                total_turnaround   += temp->turnaround;
                temp->response      = temp->waiting;
                total_response     += temp->response;
                result[result_index++] = *temp;
                temp = NULL;
                terminate++;
            }
        }
    }

    //test print
    printf("\n\nPP\n");
    printf("index\tPID\tArrival\tPrioity\tWaiting\tTurnaround\n");
    for(int i = 0; i < result_index; i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t\n", 
        i, 
        result[i].processID, 
        result[i].arrival, 
        result[i].prioity, 
        result[i].execute,
        result[i].turnaround
        );
    printf("\ntime flow:\t\t%d\naverage turnaround:\t%.2lf\naverage waiting:\t%.2lf\naverage response:\t%.2lf", 
    time_flow, total_turnaround/n, total_waiting/n, total_response/n);

}

int compare_for_RR(const void* a, const void* b) {
        
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->arrival>B->arrival)-(A->arrival<B->arrival);
}

#endif