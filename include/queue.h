/**
 * @file    queue.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   queue 자료구조
 *  
 *          [개요]
 *          기본 queue 자료구조
 * 
 * @version 0.1
 * @date    last update: 2023-05-03
 * 
 * @copyright Copyright (c) 2022 Minsu Bak
 * 
 */
#ifndef QUEUE_H
#define QUEUE_H

// standard libraray
#include <stdio.h>
#include <stdlib.h>

// external libraray
#include "process.h"

#define BUCKETS 10
#define DIGITS  4
#define MAX     10

typedef struct QueueType {
    int front, rear;
    Process queue[MAX];
}QueueType;

/**
 * @brief   queue 초기화
 * 
 * @param q queue 구조체 포인터
 */
void init_queue(QueueType *q) {
    q->front = q->rear = 0;
}

/**
 * @brief   queue의 비움 상태 확인
 * 
 * @param q queue 구조체 포인터
 * @return  int 
 */
int is_empty_q(QueueType *q) {
    return (q->front == q->rear);
}

/**
 * @brief   queue의 꽉 찬 상태 확인
 * 
 * @param q queue 구조체 포인터
 * @return  int 
 */
int is_full_q(QueueType *q) {
    return (q->front == (q->rear+1) % MAX);
}

/**
 * @brief   queue에 새 요소 삽입
 * 
 * @param q     queue 구조체 포인터
 * @param item  queue에 새로 삽입할 데이터
 */
void enqueue(QueueType *q, Process item) {
    if(is_full_q(q)) {
        fprintf(stderr, "queue is full!\n");
        exit(1);
    }
    q->rear = (q->rear + 1) % MAX;
    q->queue[q->rear] = item;
}

/**
 * @brief   queue에 기존 요소 추출
 * 
 * @param q queue 구조체 포인터
 * @return  element 
 */
Process dequeue(QueueType *q) {
    if(is_empty_q(q)) {
        fprintf(stderr, "queue is empty!\n");
        return;
    }
    q->front = (q->front + 1) % MAX;
    return q->queue[q->front];
}

#endif