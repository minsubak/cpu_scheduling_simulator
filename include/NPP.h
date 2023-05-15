/**
 * @file    NPP.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - NPP(Non-Preemption Prioity)
 *          - assign to CPU in order of prioity in the ready queue
 * @version 0.1
 * @date    2023-05-10
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef NPP_H
#define NPP_H

// external library & user define library
#include "queue.h"
#include "process.h"
#include "compare.h"

/**
 * @brief NPP.h variable info
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
 *  QueueType   ready            n           queue structure for queue(for ready queue)
 *  QueueType   pre              n           queue structure for queue(for previous queue)
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
void NPP(Process *p, int n) {
    
    // create variable, queue and etc

    int total_turnaround = 0;   
    int total_waiting    = 0;
    int total_response   = 0;
    int result_index     = 0;
    Process *temp     = NULL;
    QueueType ready, pre;

    // initalize queue
    init_queue(&ready);
    init_queue(&pre);

    // insert process to queue
    for(int i = 0; i < n; i++)
        timeout(&pre, p[i]);

    // running NPP scheduling

    int time_flow = 0; // flow of time in the scheduler
    int terminate = 0; // Number of process terminated
    while(terminate < n) {
        
        // if process arrives while time_flow value is increasing
        if(!is_empty_q(&pre)) {
            if(check(&pre).arrival == time_flow) {
                timeout(&ready, *dispatch(&pre));
                if(CHECK_PROGRESS) // debug
                    printf("arrival:\tt: %d, p: %d\n", time_flow, ready.queue->processID);
                sort(&ready, compare_for_prioity);
            }
        }
        
        // dispatch new PCB: if the previous task terminated
        if(check(&ready).arrival <= time_flow && temp == NULL) {
            temp = dispatch(&ready);
            temp->waiting = time_flow - temp->arrival;
            total_waiting += temp->waiting;
            temp->execute = 0;
            if(CHECK_PROGRESS) // debug
                printf("dispatch:\tt: %d, p: %d, w: %d\n", time_flow, temp->processID, temp->waiting);
        }

        time_flow++;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;

            // terminate present PCB
            if(temp->remain == 0) {
                if(CHECK_PROGRESS) // debug
                    printf("terminate:\tt: %d, p: %d\n", time_flow, temp->processID);
                total_turnaround      += temp->execute + temp->waiting;
                total_response        += temp->waiting;
                result[result_index++] = *temp;
                temp = NULL;
                terminate++;
            }
        }
    }

    //test print
    print_result(
        result,\
        result_index,\
        total_turnaround,\
        total_waiting,\
        total_response,\
        "NPP"
    );
}

#endif