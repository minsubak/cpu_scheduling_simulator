/**
 * @file    RR.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = preemption method - RR(Round-Robin)
 *          - 
 *          -
 *          -
 * @version 0.1
 * @date    (first date: 2023-05-15, last date: 2023-05-24)
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
 *  Process     result           y          structure for CPU scheduling result save
 *  Process     gantt            y          process task info save for gantt chart
 *  Process     p                y          structure for process data storage
 *  Process     temp             y          pointer of process structure temporary variable
 *  QueueType   ready            n          queue structure for queue(for ready queue)
 *  QueueType   pre              n          queue structure for queue(for previous queue)
 *  int         response         y          array for check the response time of the process 
 *  int         total_turnaround n          the sum of turnaround
 *  int         total_waiting    n          the sum of waiting
 *  int         total_response   n          the sum of response
 *  int         n                n          save process count
 *  int         i                n          multipurpose utilization variable
 *  int         t                n          save scheduler total burst time
 *  int         q                n          save scheduler time quantum
 *  int         time             n          flow of time in the scheduler
 *  int         terminate        n          Number of process terminated
 *  
 */

/**
 * @brief   Round-Robin
 * 
 * @param p pointer for process structure
 * @param n save process count
 * @param t save scheduler total burst time
 * @param q save scheduler time quantum
 */
void RR(Process *p, int n, int t, int q) {
    
    // create variable, queue and etc

    int total_turnaround = 0;                    // the sum of turnaround
    int total_waiting    = 0;                    // the sum of waiting
    int total_response   = 0;                    // the sum of response
    int time             = 0;                    // flow of time in the scheduler
    int terminate        = 0;                    // number of process terminated
    int *response   = malloc(sizeof(int)*n);     // array for check the response time of the process 
    Process *gantt  = malloc(sizeof(Process)*t); // process task info save for gantt chart
    Process *result = malloc(sizeof(Process)*n); // structure for CPU scheduling result save
    Process *temp  = NULL;                       // pointer of process structure temporary variable
    QueueType ready;                             // queue structure for queue(for ready queue)
    QueueType pre;                               // queue structure for queue(for previous queue)

    // initalize array
    for(int i = 0; i < n; i++)
        response[i] = 0;

    // initalize queue
    init_queue(&ready);
    init_queue(&pre);

    // insert process to queue
    for(int i =0; i < n; i++)
        enqueue(&pre, p[i]);

    // sort by arrival
    sort(&pre, compare_for_arrival);

    // running RR scheduling
    while(terminate < n) {

        // if process arrives while time value is increasing
        if(!is_empty_q(&pre)) {
            if(peek(&pre).arrival == time) {
                enqueue(&ready, *dequeue(&pre));
                if(CHECK) // debug
                    printf("arrival:\tt: %2d, p: %2d\n", time, ready.queue->processID);
            }
        }

        // dispatch new PCB: if the previous task terminated
        if(peek(&ready).arrival <= time && temp == NULL) {
            temp = dequeue(&ready);
            temp->waiting  = time - temp->timeout;
            total_waiting += temp->waiting;
            temp->execute  = 0;
            if(CHECK) // debug
                printf("dispatch:\tt: %2d, p: %2d, w: %2d\n", time, temp->processID, temp->waiting);
        }

        // 
        if(temp->execute == q) {
            if(CHECK) // debug
                printf("timeout:\tt: %2d, p: %2d, w: %2d\n", time, temp->processID, temp->waiting);
            temp->timeout          = time;
            total_turnaround      += temp->execute + temp->waiting;
            enqueue(&ready, *temp);
            temp = dequeue(&ready);
            temp->waiting          = time - temp->timeout;
            total_waiting         += temp->waiting;
            temp->execute          = 0;
            if(CHECK) // debug
                printf("dispatch:\tt: %2d, p: %2d, w: %2d\n", time, temp->processID, temp->waiting);
        }
        
        // check the response time of the process 
        if(response[temp->processID] == 0) {
            response[temp->processID] = -1;
            total_response += time - temp->arrival;
        }
        
        gantt[time++] = *temp;

        // scheduler task progress
        if(temp != NULL) {
            temp->remain--;
            temp->execute++;
            
            // terminate present PCB
            if(temp->remain == 0) {
                if(CHECK) // debug
                    printf("terminate:\tt: %2d, p: %2d\n", time, temp->processID);
                total_turnaround   += temp->execute + temp->waiting;
                result[terminate++] = *temp;
                temp = NULL;
            }
        }
    }

    // gantt chart test
    //print_gantt(gantt, time, n, "RR");
            
    // print RR scheduling result
    print_result(result, n, "RR", total_turnaround, total_waiting, total_response);

    // memory allocate disable
    free(response);
    free(gantt);
    free(result);
}

#endif