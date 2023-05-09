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
 *  
 */

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
    
    int i = 0;
    while(i < count) {
        fscanf(fp, "%d %d %d %d\n", 
        &p[i].processID, 
        &p[i].arrival, 
        &p[i].burst, 
        &p[i].prioity
        );
        p[i].remain = p[i].burst;
        i++;
    }

    // First Come First Served
    FCFS(p, count);

    // Shortest Job First
    SJF(p, count);

    // Non-Preemption Prioity
    NPP(p, count);
    
    // Preemption Prioity
    // PP(p, count);

    // Round-Robin
    // RR(p, count);

    // Shortest Remaining Time
    // SRT(p, count);

    // Highest Responese Ratio Next
    // HRN(p, count);

    // memory allocate disable
    free(p);
    fclose(fp);
    return 0;
}