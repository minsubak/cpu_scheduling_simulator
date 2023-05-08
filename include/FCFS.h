/**
 * @file    FCFS.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   CPU 스케줄링 시뮬레이터-선점형 스케줄링 기법
 * @version 0.1
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */

#ifndef FCFS_H
#define FCFS_H

#include "queue.h"
#include "process.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief 오름차순 비교 함수(w. qsort)
 * 
 * @param a compare target a
 * @param b compare target b
 * @return int 
 */
int compare(const void *a, const void *b)
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

void FCFS(Process *p, int n) {
    
    // file io test
    printf("FCFS.h file i/o data test\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].index, p[i].arrival, p[i].working, p[i].prioity);
    }

    int arrival_array[5]; // arrival sort array

    for(int i = 0; i < n; i ++)
        arrival_array[i] = p[i].arrival;

    qsort(arrival_array, sizeof(arrival_array) / sizeof(int), sizeof(int), compare);

    printf("\n");
    for(int i = 0; i < n; i++)
        printf("%d\t", arrival_array[i]);
    
}

#endif