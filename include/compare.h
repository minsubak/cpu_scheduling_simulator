/**
 * @file    compare.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   user define library for compare function for qsort()
 * @version 0.1
 * @date    (first date: 2023-05-15, last date: 2023-05-24)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef COMPARE_H
#define COMPARE_H

// external library && user define library
#include "process.h"
#include "queue.h"

/**
 * @brief compare.h variable info
 *  
 *  type        name        pointer     info
 *  const void  a           y           compare target a
 *  const void  b           y           compare traget b
 *  Process     A           y           compare target A(w. using a)
 *  Process     B           y           compare target B(w. using b)
 * 
 */

/**
 * @brief   compare arrival function with qsort
 * 
 * @param a compare target a
 * @param b compare target b
 * @return  int 
 */
int compare_for_arrival(const void* a, const void* b) {
        
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->arrival>B->arrival)-(A->arrival<B->arrival);
}

/**
 * @brief   compare burst function with qsort
 * 
 * @param a compare target a
 * @param b compare target b
 * @return  int 
 */
int compare_for_burst(const void* a, const void* b) {
    
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->burst>B->burst)-(A->burst<B->burst);
}

/**
 * @brief   compare prioity function with qsort
 * 
 * @param a compare target a
 * @param b compare target b
 * @return  int 
 */
int compare_for_prioity(const void* a, const void* b) {
    
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    // if compare target A and B was same
    if(A->prioity == B->prioity)
        return (A->arrival>B->arrival)-(A->arrival<B->arrival);
    return (A->prioity>B->prioity)-(A->prioity<B->prioity);
}

/**
 * @brief   compare remain function with qsort
 * 
 * @param a compare target a
 * @param b compare target b
 * @return int 
 */
int compare_for_remain(const void* a, const void* b) {
    
    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (A->remain>B->remain)-(A->remain<B->remain);
}

/**
 * @brief   compare prioity, but using special formula function with qsort
 *          prioity = (waiting + burst) / burst
 * 
 * @param a compare target a
 * @param b compare target b
 * @return int 
 */
int compare_for_HRN(const void* a, const void* b) {

    // compare target match progress

    Process* A = (Process*) a;
    Process* B = (Process*) b;

    return (((A->waiting + A->burst) / A->burst) > ((B->waiting + B->burst) / B->burst)) - (((A->waiting + A->burst) / A->burst) < ((B->waiting + B->burst) / B->burst));
}

#endif