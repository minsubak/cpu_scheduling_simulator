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
#include <main.h>

int main() {
    
    FILE *fp = fopen("data.txt", "r");
    if(fp == NULL)
        error("file not found");
    printf("file found!");

    

    return 0;
}