#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "subject/subject.h"
#include "config.h"

typedef struct {
    char name[MAX_NAME_LENGTH];
    double score;
} failSubject;

typedef struct {
    failSubject subject[MAX_SUBJECT_NUM];
    int front;
    int rear;
} Queue;

// 初始化队列
void initQueue(Queue *q) ;

// 检查队列是否为空
bool isEmpty(Queue *q) ;

// 检查队列是否已满
bool isFull(Queue *q) ;

// 入队操作
bool enqueue(Queue *q, failSubject subject);

// 出队操作

bool dequeue(Queue *q);

// 获取队首元素
failSubject first(Queue *q) ;

// 打印队列内容
void printQueue(Queue *q) ;

#endif