/**
 * @file    FCFS.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   CPU schedule simulator
 *          non preemeption schuduling method
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
#include <time.h>

// external library
#include "queue.h"
#include "process.h"

/**
 * @brief FCFS.h variable info
 *  
 *  type        name        pointer     info
 *  Process     p           y           structure for process data storage
 *  int         i           n           multipurpose utilization variable
 *  Process     tmp         n           process structure temporary variable
 *  int         j           n           multipurpose utilization variable
 *  int         n           n           save process count
 *  QueueType   q           n           structure for Queue algorithm and data storage
 *  
 */

/**
 * @brief First Come First Served
 * 
 * @param p Process Structer Pointer
 * @param n Process count
 */
void FCFS(Process *p, int n) {

    Process tmp;

    // sort by arrival
    for(int i = 0; i < n; i ++)
        for(int j = 0 ; j < i; j++)
            if(p[i].arrival < p[j].arrival) {
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }

    // create queue & insert process
    QueueType q;
    init_queue(&q);
    for(int i = 0; i < n; i++)
        enqueue(&q, p[i]);

    printf("FCFS Scheduler test print\n");
    printf("Index\tNo.\tArrival\tWorking\tPrioity\n");
    for(int i = 0; i < n; i++) {
        tmp = dequeue(&q);        
        printf("%d\t%s\t%d\t%d\t%d\n", 
        i,
        tmp.pID, 
        tmp.arrival, 
        tmp.working, 
        tmp.prioity
        );
    }
    printf("pass\n");

}

#endif