/**
 * @file    RR.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = preemption method - RR(Round-Robin)
 *          - 
 * @version 0.1
 * @date    (first date: 2023-05-15)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef RR_H
#define RR_H

// external library & user define library
#include "queue.h"
#include "process.h"
#include "compare.h"

/**
 * @brief RR.h variable info
 *  
 *  type        name             pointer    info
 *  Process     result           y          CPU scheduling result storage structure, reference from "process.h"
 *  Process     p                y          structure for process data storage
 *  Process     temp             y          pointer of process structure temporary variable
 *  QueueType   ready            n          queue structure for queue(for ready queue)
 *  QueueType   pre              n          queue structure for queue(for previous queue)
 *  int         total_turnaround n          the sum of turnaround
 *  int         total_waiting    n          the sum of waiting
 *  int         total_response   n          the sum of response
 *  int         result_index     n          index for result array
 *  int         n                n          save process count
 *  int         t                n          time slice(quantom)
 *  int         i                n          multipurpose utilization variable
 *  int         time_flow        n          flow of time in the scheduler
 *  int         terminate        n          Number of process terminated
 *  
 */

extern Process result[MAX];

/**
 * @brief   Round-Robin
 * 
 * @param p pointer for process structure
 * @param n process count
 */
void RR(Process *p, int n, int t) {
    
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
    for(int i =0; i < n; i++)
        timeout(&pre, p[i]);

    // sort by arrival
    sort(&pre, compare_for_arrival);

    // running RR scheduling

    int time_flow = 0;
    int terminate = 0;
    while(terminate < n) {

        // if process arrives while time_flow value is increasing
        if(!is_empty_q(&pre)) {
            if(peek(&pre).arrival == time_flow) {
                timeout(&ready, *dispatch(&pre));
                if(CHECK) // debug
                    printf("arrival:\tt: %2d, p: %2d\n", time_flow, ready.queue->processID);
            }
        }

        // dispatch new PCB: if the previous task terminated
        if(peek(&ready).arrival <= time_flow && temp == NULL) {
            temp = dispatch(&ready);
            temp->waiting  = time_flow = temp->timeout;
            total_waiting += temp->waiting;
            temp->execute  = 0;
        }
    }
}

#endif