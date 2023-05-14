/**
 * @file    compare.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   user define library of compare function for qsort()
 * @version 0.1
 * @date    2023-05-15
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef COMPARE_H
#define COMPARE_H

// external library && user define library
#include "process.h"
#include "queue.h"

int compare_for_arrival(const void* a, const void* b) {
        
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->arrival>B->arrival)-(A->arrival<B->arrival);
}

#endif