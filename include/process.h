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

/**
 * @brief process.h variable info
 *  
 *  type        name        pointer     info
 *  #define     LEN         n           process no. array size
 *  char        pID         y           process no.
 *  int         arrival     n           process arrival time
 *  int         working     n           process working time
 *  int         prioity     n           process prioity
 * 
 */

#define LEN 10      // process no. array size

/**
 * @brief structure for process
 * 
 */
typedef struct Process{
    char pID[LEN];  // process no.
    int arrival;    // process arrival time
    int working;    // process working time
    int prioity;    // process prioity
} Process;



#endif