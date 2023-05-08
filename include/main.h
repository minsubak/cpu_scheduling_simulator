#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"
#include "SJF.h"
#include "NPP.h"
#include "PP.h"
#include "RR.h"
#include "SRT.h"
#include "HRN.h"

/**
 * @brief print error and exit
 * 
 * @param message print error info message
 */
void error(char * message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

/**
 * @brief 오름차순 비교 함수(w. qsort)
 * 
 * @param a compare target a
 * @param b compare target b
 * @return int 
 */
/* int compare(const void *a, const void *b)
{
    // void 포인터를 int 포인터 변환 후 역참조
    int num1 = *(int *)a;
    int num2 = *(int *)b;

    if (num1 < num2)    // case: a < b
        return -1;      // -1 return
    
    if (num1 > num2)    // case: a > b
        return 1;       // 1 return
    
    return 0;    // a = b, return 1
} */

#endif