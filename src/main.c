/**
 * @file    main.c
 * @author  mindou (minsu5875@naver.com)
 * @brief   Operating System-Term Project: CPU_SCHEDULER
 * @version 0.1
 * @date    (first date: 2023-04-26)
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#include "main.h"
#include "process.h"
#include "FCFS.h"
#include <time.h>

int main() {
    
    FILE *fp = fopen("data.txt", "r");
    if(fp == NULL)
        error("file not found");
    printf("file found!");

    int tmp, cnt = 0;
    while(!feof(fp)) {
        fscanf(fp, "%d ", &tmp);
        fscanf(fp, "%d ", &tmp);
        fscanf(fp, "%d ", &tmp);
        fscanf(fp, "%d\n", &tmp);
        cnt++;
    } rewind(fp);
    
    Process *p = malloc(sizeof(Process)*cnt);
    cnt = 0;

    while(!feof(fp)) {
        fscanf(fp, "%d ", &tmp);
        p[cnt].index = tmp;
        fscanf(fp, "%d ", &tmp);
        p[cnt].arrival = tmp;
        fscanf(fp, "%d ", &tmp);
        p[cnt].working = tmp;
        fscanf(fp, "%d\n", &tmp);
        p[cnt].prioity = tmp;
        cnt++;
    }
    // FCFS
    FCFS(*p);


    // Memory Allocate Disable
    free(p);
    fclose(fp);
    return 0;
}