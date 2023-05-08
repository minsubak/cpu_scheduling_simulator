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
    printf("file found!\n");

    int tmp, cnt = 0;
    while(!feof(fp)) {
        fscanf(fp, "%d ", &tmp);
        fscanf(fp, "%d ", &tmp);
        fscanf(fp, "%d ", &tmp);
        fscanf(fp, "%d\n", &tmp);
        cnt++;
    } rewind(fp);
    
    printf("%d\n", cnt);
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

    // file io test
    printf("main.c file i/o data test\n");
    for(int i = 0; i < cnt; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].index, p[i].arrival, p[i].working, p[i].prioity);
    }

    printf("\n");
    // FCFS
    FCFS(p, cnt);


    // Memory Allocate Disable
    free(p);
    fclose(fp);
    return 0;
}