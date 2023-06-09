/**
 * @file    queue.h
 * @author  Mindou (minsu5875@naver.com)
 * @brief   basic queue structure / edit for CPU scheduler simulator
 * @version 0.1
 * @date    (last update: 2023-05-31)
 * 
 * @copyright Copyright (c) 2022 Minsu Bak
 * 
 */
#ifndef QUEUE_H
#define QUEUE_H

// standard libraray
#include <stdio.h>
#include <stdlib.h>

// external libraray & user define library
#include "process.h"

/**
 * @brief queue.h variable info
 * 
 *  type        name        pointer     info
 *  #define     MAX         n           queue storage size
 *  int         front       n           queue front data flag
 *  int         rear        n           queue rear data flag
 *  Process     queue       y           structre queue array for Process data storage
 *  QueueType   q           y           structure for queue data storage
 *  Process     item        n           insert target
 * 
 */

#define MAX 100

typedef struct QueueType {

    int front, rear;
    Process queue[MAX];
    
}QueueType;

/**
 * @brief   init queue
 * 
 * @param q pointer for queue structure
 */
void init_queue(QueueType *q) {
    
    q->front = q->rear = 0;
}

/**
 * @brief   check the queue status is empty
 * 
 * @param q pointer for queue structure
 * @return  int 
 */
int is_empty_q(QueueType *q) {

    return (q->front == q->rear);
}

/**
 * @brief   check the queue status is full
 * 
 * @param q pointer for queue structure
 * @return  int 
 */
int is_full_q(QueueType *q) {

    return (q->front == (q->rear+1) % MAX);
}

/**
 * @brief   insert new process data into queue
 * 
 * @param q     pointer for queue structure
 * @param item  insert target
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
 * @brief   extract process data from the queue
 * 
 * @param q pointer for queue structure
 * @return  Process
 */
Process* dequeue(QueueType *q) {

    if(is_empty_q(q)) {
        fprintf(stderr, "queue is empty!\n");
        return;
    }
    q->front = (q->front + 1) % MAX;
    return &q->queue[q->front];
}

/**
 * @brief   check process data from the queue
 * 
 * @param q pointer for queue structure
 * @return Process 
 */
Process peek(QueueType *q) {

    if(is_empty_q(q)) return;
    return q->queue[(q->front + 1) % MAX];
}

/**
 * @brief   sort processes in the queue using with qsort()
 * 
 * @param q pointer for queue structure
 * @param compare compare target
 */
void sort(QueueType *q, int(*compare)(const void* a, const void* b)) {

    qsort(q->queue + q->front + 1, q->rear-q->front, sizeof(Process), compare);
}

#endif