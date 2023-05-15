/**
 * @file    process.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   CPU scheduler simulator process header
 * @version 0.1
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef PROCESS_H
#define PROCESS_H

// standard libaray
#include <stdbool.h>

/**
 * @brief process.h variable info
 *  
 *  type        name        pointer     info
 *  int         processID   n           process no.
 *  int         arrival     n           process arrival time
 *  int         burst       n           process burst time
 *  int         remain      n           process remain time
 *  int         prioity     n           process prioity
 *  int         turnaround  n           save process turnaround time (will delete soon)
 *  int         response    n           save process response time   (will delete soon)
 *  int         waiting     n           save process waiting time
 *  int         terminate   n           process terminate flag(0|1)
 *  Process     original    y           original process structure
 *  Process     target      y           overwrite target
 * 
 */

#define MAX             1024
#define CHECK_PROGRESS  true

/**
 * @brief structure for process
 * 
 */
typedef struct Process{

    int processID;  // process no.
    int arrival;    // process arrival time
    int burst;      // process burst time
    int remain;     // process remain time()
    int prioity;    // process prioity
    int turnaround; // save process turnaround time
    int response;   // save process response time
    int waiting;    // save process waiting time
    int terminate;  // process terminate flag(0|1)
    int timeout;
    int execute;

} Process;

void print_result(Process *p, int n, int t, int w, int r, char* name) {

    printf("\n\n%s\n", name);
    printf("index\tPID\tarrival\tburst\tprioity\twaitng\tturnaround\n");
    for(int i = 0; i < n ;i++)
        printf("%d\tP%d\t%d\t%d\t%d\t%d\t%d\n", 
        i,\
        p[i].processID,\
        p[i].arrival,\
        p[i].burst,\
        p[i].prioity,\
        p[i].waiting,\
        (p[i].execute + p[i].waiting)
        );
    printf("turnaround average:\t%.1lf\n", (double)t/n);
    printf("waiting average:\t%.1lf\n", (double)w/n);
    printf("response average:\t%.1lf\n", (double)r/n);
}

#endif