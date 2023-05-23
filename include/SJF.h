/**
 * @file    SJF.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - SJF(Shortest Job First)
 *          - assign to CPU in order of burst time in the ready queue
 *          - improve efficiency by reducing the Conboy effect
 *          -
 * @version 0.1
 * @date    (first date: 2023-05-09, last date: 2023-05-24)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef SJF_H
#define SJF_H

// external library & user define library
#include "queue.h"
#include "process.h"
#include "compare.h"

/**
 * @brief SJF.h variable info
 *  
 *  type        name             pointer    info
 *  Process     result           y          structure for CPU scheduling result save
 *  Process     gantt            y          process task info save for gantt chart
 *  Process     p                y          structure for process data storage
 *  Process     temp             y          pointer of process structure temporary variable
 *  QueueType   ready            n          queue structure for queue(for ready queue)
 *  QueueType   pre              n          queue structure for queue(for previous queue)
 *  int         total_turnaround n          the sum of turnaround
 *  int         total_waiting    n          the sum of waiting
 *  int         total_response   n          the sum of response
 *  int         n                n          save process count
 *  int         i                n          multipurpose utilization variable
 *  int         t                n          save scheduler total burst time
 *  int         time             n          flow of time in the scheduler
 *  int         terminate        n          Number of process terminated
 *  
 */

/**
 * @brief   Shortest Job First
 * 
 * @param p pointer for process struture
 * @param n save process count
 * @param t save scheduler total burst time
 */
void SJF(Process *p, int n, int t) {
    
    // create variable, queue and etc

    int total_turnaround = 0;                   // the sum of turnaround
    int total_waiting    = 0;                   // the sum of waiting
    int total_response   = 0;                   // the sum of response
    int time             = 0;                   // flow of time in the scheduler
    int terminate        = 0;                   // number of process terminated
    Process *temp  = NULL;                      // pointer of process structure temporary variable
    Process *gantt = malloc(sizeof(Process)*t); // process task info save for gantt chart
    Process result[5];                          // structure for CPU scheduling result save
    QueueType ready;                            // queue structure for queue(for ready queue)
    QueueType pre;                              // queue structure for queue(for previous queue)

    // initalize queue
    init_queue(&ready);
    init_queue(&pre);

    // insert process to queue
    for(int i = 0; i < n; i++)
        enqueue(&pre, p[i]);

    // sort by arrival
    sort(&pre, compare_for_arrival);

    // running SJF scheduling
    while(terminate < n) {
        
        // insert process into the ready queue in order of arrive
        if(!is_empty_q(&pre)) {
            if(peek(&pre).arrival == time) {
                enqueue(&ready, *dequeue(&pre));
                if(CHECK) // debug
                    printf("arrival:\tt: %2d, p: %2d\n", time, ready.queue->processID);
                sort(&ready, compare_for_burst);
            }
        }
        
        // dispatch new PCB: if the previous task terminated
        if(peek(&ready).arrival <= time && temp == NULL) {
            temp = dequeue(&ready);
            temp->waiting  = time - temp->arrival;
            total_waiting += temp->waiting;
            temp->execute  = 0;
            if(CHECK) // debug
                printf("dispatch:\tt: %2d, p: %2d, w: %2d\n", time, temp->processID, temp->waiting);
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
                total_response     += temp->waiting;
                result[terminate++] = *temp;
                temp                = NULL;
            }
        }
    }

    // gantt chart test
    /*
    print_result(
        gantt,\
        time,\
        n,\
        "SJF"
    ); */

    // print SJF scheduling result
    printf("\nSJF\n");
    printf("index\tPID\tarrival\tburst\tprioity\twaitng\tturnaround\n");
    for(int i = 0; i < terminate ;i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t%d\n", 
        i,\
        result[i].processID,\
        result[i].arrival,\
        result[i].burst,\
        result[i].prioity,\
        result[i].waiting,\
        (result[i].execute + result[i].waiting)
    );
    printf("turnaround average:\t%.1lf\n", (double)total_turnaround/n);
    printf("   waiting average:\t%.1lf\n", (double)total_waiting/n);
    printf("  response average:\t%.1lf\n", (double)total_response/n);  

    // memory allocate disable
    free(gantt);
}

#endif