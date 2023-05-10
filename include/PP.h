/**
 * @file    PP.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - PP(Preemption Prioity)
 *          - 
 *          - 
 * 
 * @version 0.1
 * @date    2023-05-11
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef PP_H
#define PP_H

// standard library
#include <stdlib.h>

// external library & user define library
#include "queue.h"
#include "process.h"

/**
 * @brief PP.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result_pp        y           CPU scheduling result_pp storage structure
 *  double      total_turnaround n           the sum of turnaround
 *  double      total_waiting    n           the sum of waiting
 *  double      total_response   n           the sum of response
 *  int         result_index     n           index for result array
 *  void        a                y           compare target variable a
 *  void        b                y           compare target variable b
 *  Process     A                y           compare target variable A(w. using void* a)
 *  Process     B                y           compare target variable B(w. using void* b)
 *  Process     p                y           pointer for process structure
 *  int         n                n           save process count
 *  QueueType   ready            n           queue structure for queue(for ready queue)
 *  QueueType   pre              n           queue structure for queue(for previous queue)
 *  int         i                n           multipurpose utilization variable
 *  int         time_flow        n           flow of time in the scheduler
 *  int         terminate        n           Number of process terminated
 *  
 */

Process result_pp[1024];

/**
 * @brief   compare function with qsort()
 * 
 * @param a compare target a
 * @param b compare target b
 * @return  int 
 */
int compare_for_PP(const void* a, const void* b);

/**
 * @brief   Non-Preemption Prioity
 * 
 * @param p pointer for process struture
 * @param n process count
 */
void PP(Process *p, int n) {
    
    double total_turnaround = 0;   
    double total_waiting    = 0;
    double total_response   = 0;
    int    result_index     = 0;

    // create ready queue & insert process to ready queue

    QueueType ready;
    init_queue(&ready);

    QueueType pre;
    init_queue(&pre);
    for(int i = 0; i < n; i++)
        timeout(&pre, p[i]);

    // running PP scheduling

    Process *temp = NULL;
    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {

        // if process arrives while time_flow value is increasing
        if(!is_empty_q(&pre)) {
            if(check(&pre).arrival == time_flow) {
                timeout(&ready, *dispatch(&pre));
                //printf("arrival! - t: %d\n", time_flow);
                sort(&ready, compare_for_PP);
            }
        }

        // dispatch new PCB and time-out present PCB
        if(!is_empty_q(&ready)) {
            if(check(&ready).arrival <= time_flow && temp == NULL) {
                temp = dispatch(&ready);
                //printf("dispatch - t: %d p: %d w: %d\n", time_flow, temp->processID, temp->waiting);
                temp->waiting = time_flow - temp->timeout;
                total_waiting += temp->waiting;
                temp->execute = 0;
            }
        }

        // check prioity value during operation
        if(!is_empty_q(&ready)) {
            if(check(&ready).prioity < temp->prioity) {
                temp->timeout = time_flow;
                //printf("timeout! - t: %d p: %d\n", time_flow, temp->processID);
                temp->turnaround    = temp->execute + temp->waiting;
                total_turnaround   += temp->turnaround;
                temp->response      = temp->waiting;
                total_response     += temp->response;
                result_pp[result_index].execute = temp->execute;
                result_pp[result_index++] = *temp;
                timeout(&ready, *temp);
                temp = dispatch(&ready);
                sort(&ready, compare_for_PP);
            }            
        }

        time_flow++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;

            // terminate present PCB
            if(temp->remain == 0) {
                //printf("terminate! - t: %d p: %d\n", time_flow, temp->processID);
                temp->turnaround    = temp->execute + temp->waiting;
                total_turnaround   += temp->turnaround;
                temp->response      = temp->waiting;
                total_response     += temp->response;
                result_pp[result_index++] = *temp;
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
        result_pp[i].processID, 
        result_pp[i].arrival, 
        result_pp[i].prioity, 
        result_pp[i].execute,
        result_pp[i].turnaround
        );
    printf("\ntime flow:\t\t%d\naverage turnaround:\t%.2lf\naverage waiting:\t%.2lf\naverage response:\t%.2lf", 
    time_flow, total_turnaround/n, total_waiting/n, total_response/n);
}

int compare_for_PP(const void* a, const void* b) {
    
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    // if compare target A and B was same
    if(A->prioity == B->prioity) {
        return (A->arrival>B->arrival)-(A->arrival<B->arrival);
    }

    return (A->prioity>B->prioity)-(A->prioity<B->prioity);
} 

#endif