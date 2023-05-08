/**
 * @file    compare.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   qsort를 위한 compare 함수 헤더
 * @version 0.1
 * @date    2023-05-08
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef COMPARE_H
#define COMPARE_H

/**
 * @brief 오름차순 비교 함수(w. qsort(#include <stdlib.h>))
 * 
 * @param a compare target a
 * @param b compare target b
 * @return int 
 */
int compareByArrival(const void *a, const void *b)
{
    // void 포인터를 int 포인터 변환 후 역참조
    int num1 = *(int *)a;
    int num2 = *(int *)b;

    if (num1 < num2)    // case: a < b
        return -1;      // -1 return
    
    if (num1 > num2)    // case: a > b
        return 1;       // 1 return
    
    return 0;    // a = b, return 1
}

#endif COMPARE_H