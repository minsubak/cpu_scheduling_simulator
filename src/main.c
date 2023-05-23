/**
 * @file    main.c
 * @author  Mindou (minsu5875@naver.com)
 * @brief   Operating System-Term Project: CPU_Scheduler Simulator
 * @version 0.1
 * @date    (first date: 2023-04-26)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

// standard library
#include <stdio.h>
#include <stdlib.h>

// external library & user define library
#include "main.h"
#include "process.h"

/**
 * @brief main.c variable info
 *  
 *  type        name        pointer     info
 *  FILE        fp          y           file pointer for file I/O and management
 *  Process     o           y           structure for process data storage(original)
 *  Process     t           y           structure for process data storage(target)
 *  int         i           n           multipurpose utilization variable
 *  int         count       n           save process count
 *  int         timeSlice   n           save simulator environment variable basic value
 *  
 */

Process RESET;

int main() {
    
    // search and load "data.txt" files with process data

    FILE *fp = fopen("data.txt", "r");
    if(fp == NULL) error("file not found");
    else printf("file found!\n\n");

    // read process count and allocate memory

    int count = 0;
    fscanf(fp, "%d\n", &count);
    Process *p = malloc(sizeof(Process)*count);

    // read and save process data

    int total = 0;
    for(int i = 0; i < count; i++) {
        fscanf(fp, "%d %d %d %d\n",\
        &p[i].processID,\
        &p[i].arrival,\
        &p[i].burst,\
        &p[i].prioity
        );
        p[i].remain = p[i].burst;
        p[i].timeout = p[i].arrival;
        p[i].waiting = 0;
        p[i].execute = 0;
        total += p[i].burst;
    }

    int quantum;
    fscanf(fp, "%d", &quantum);

    // First Come First Served
    //FCFS(p, count, total);

    // Shortest Job First
    //SJF(p, count, total);

    // Highest Responese Ratio Next
    //HRN(p, count, total);

    // Non-Preemption Prioity
    //NPP(p, count, total);
    
    // Preemption Prioity
    //PP(p, count, total);

    // Round-Robin
    RR(p, count, total, quantum);

    // Shortest Remaining Time
    //SRT(p, count, total);

    // memory allocate disable
    free(p);
    fclose(fp);
    return 0;
}