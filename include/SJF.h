/**
 * @file    SJF.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   = CPU schedule simulator
 *          = non preemeption method - SJF(Shortest Job First)
 *          - assign to CPU in order of burst time in the ready queue
 *          - improve efficiency by reducing the Conboy effect
 * 
 * @version 0.1
 * @date    2023-05-09
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef SJF_H
#define SJF_H

// standard library
#include <stdlib.h>

// external library & user define library
#include "queue.h"
#include "process.h"

/**
 * @brief SJF.h variable info
 *  
 *  type        name             pointer     info
 *  Process     result           y           CPU scheduling result storage structure
 *  double      total_turnaround n           the sum of turnaround
 *  double      total_waiting    n           the sum of waiting
 *  double      total_response   n           the sum of response
 * 
 */

Process result[5];
double  total_turnaround;   
double  total_waiting;
double  total_response;

/**
 * @brief   sort by burst with process
 * 
 * @param p pointer for process structure
 * @return  Process 
 */
Process sort_by_burst(Process *p);

/**
 * @brief   Shortest Job First
 * 
 * @param p pointer for process struture
 * @param n process count
 */
void SJF(Process *p, int n) {
    
}



#endif