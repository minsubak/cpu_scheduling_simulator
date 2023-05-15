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

Process result[MAX];
Process RESET;

/**
 * @brief   initalize result array
 * 
 * @param p pointer for process structure, initalize target
 */
void init_result(Process* r);

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
        i++;
    }

    // read simulator environment variable basic value

    int timeSlice;
    fscanf(fp, "%d\n", &timeSlice);

    // First Come First Served
    //FCFS(p, count);
    //init_result(result);

    // Shortest Job First
    //SJF(p, count);
    //init_result(result);

    // Non-Preemption Prioity
    NPP(p, count);
    //init_result(result);
    
    // Preemption Prioity
    //PP(p, count);
    //init_result(result);

    // Round-Robin
    // RR(p, count, timeSlice);
    //init_result(result);

    // Shortest Remaining Time
    // SRT(p, count, timeSlice);
    init_result(result);

    // Highest Responese Ratio Next
    // HRN(p, count, timeSlice);

    // memory allocate disable
    free(p);
    fclose(fp);
    return 0;
}

void init_result(Process* p) {
    
    for(int i = 0; i < MAX; i++)
        p[i] = RESET;
}