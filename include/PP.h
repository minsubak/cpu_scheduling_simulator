/**
 * @file    PP.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - PP(Preemption Prioity)
 *          - 
 *          - 
 * @version 0.1
 * @date    (first date: 2023-05-11)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef PP_H
#define PP_H

// external library & user define library
#include "queue.h"
#include "process.h"
#include "compare.h"

/**
 * @brief PP.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result           y           CPU scheduling result storage structure, reference from "process.h"
 *  Process     p                y           structure for process data storage
 *  Process     temp             y           pointer of process structure temporary variable
 *  QueueType   ready            n           queue structure for queue(for ready queue)
 *  QueueType   pre              n           queue structure for queue(for previous queue)
 *  int         total_turnaround n           the sum of turnaround
 *  int         total_waiting    n           the sum of waiting
 *  int         total_response   n           the sum of response
 *  int         result_index     n           index for result array
 *  int         n                n           save process count
 *  int         i                n           multipurpose utilization variable
 *  int         time_flow        n           flow of time in the scheduler
 *  int         terminate        n           Number of process terminated
 *  
 */

extern Process result[MAX];

/**
 * @brief   Non-Preemption Prioity
 * 
 * @param p pointer for process struture
 * @param n process count
 */
void PP(Process *p, int n) {
    
    // create variable, queue and etc

    double total_turnaround = 0;   
    double total_waiting    = 0;
    double total_response   = 0;
    int    result_index     = 0;
    Process *temp        = NULL;
    QueueType ready, pre;

    // initalize queue
    init_queue(&ready);
    init_queue(&pre);

    // insert process to queue
    for(int i = 0; i < n; i++)
        enqueue(&pre, p[i]);

    // running PP scheduling

    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {

        // if process arrives while time_flow value is increasing
        if(!is_empty_q(&pre)) {
            if(peek(&pre).arrival == time_flow) {
                enqueue(&ready, *dequeue(&pre));
                if(CHECK) // debug
                    printf("arrival:\tt: %2d, p: %2d\n", time_flow, ready.queue->processID);
                sort(&ready, compare_for_prioity);
            }
        }

        // dispatch new PCB: if the previous task terminated
        if(peek(&ready).arrival <= time_flow && temp == NULL) {
            temp = dequeue(&ready);
            temp->waiting  = time_flow - temp->timeout;
            total_waiting += temp->waiting;
            temp->execute  = 0;
            if(CHECK) // debug
                printf("dispatch:\tt: %2d, p: %2d, w: %2d\n", time_flow, temp->processID, temp->waiting);
        }

        // check prioity during operation
        if(!is_empty_q(&ready)) {
            if(peek(&ready).prioity < temp->prioity) {
                if(CHECK)
                    printf("timeout:\tt: %2d, p: %2d\n", time_flow, temp->processID);
                temp->timeout          = time_flow;
                total_turnaround      += temp->execute + temp->waiting;
                total_response        += temp->waiting;
                result[result_index++] = *temp;
                enqueue(&ready, *temp);
                temp = dequeue(&ready);
                temp->waiting          = time_flow - temp->timeout;
                total_waiting         += temp->waiting;
                temp->execute          = 0;
                if(CHECK) // debug
                    printf("dispatch:\tt: %2d, p: %2d, w: %2d\n", time_flow, temp->processID, temp->waiting);
                sort(&ready, compare_for_prioity);
            }            
        }

        time_flow++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;

            // terminate present PCB
            if(temp->remain == 0) {
                if(CHECK)
                    printf("terminate:\tt: %2d, p: %2d\n", time_flow, temp->processID);
                total_turnaround      += temp->execute + temp->waiting;
                total_response        += temp->waiting;
                result[result_index++] = *temp;
                temp = NULL;
                terminate++;
            }
        }
    }

    //test
    print_result(
        result,\
        result_index,\
        n,\
        total_turnaround,\
        total_waiting,\
        total_response,\
        "PP"
    );
}

#endif