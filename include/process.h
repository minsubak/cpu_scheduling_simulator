/**
 * @file    process.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   CPU 스케줄러 시뮬레이터 프로세스 헤더 파일
 * @version 0.1
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023 Minsu Bak
 * 
 */
#ifndef PROCESS_H
#define PROCESS_H

/**
 * @brief 프로세스 구조체
 * 
 * @var index   프로세스 번호
 * @var arrival 프로세스 도착 시간
 * @var working 프로세스 작업 시간
 * @var prioity 프로세스 우선 순위
 */
typedef struct Process{
    int index;
    int arrival;
    int working;
    int prioity;
} Process;



#endif