#include "interface/interface.h"

// 初始化队列
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

// 检查队列是否为空
bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

// 检查队列是否已满
bool isFull(Queue *q) {
    return (q->rear + 1) % MAX_SUBJECT_NUM == q->front;
}

// 入队操作
bool enqueue(Queue *q, failSubject subject) {
    if (isFull(q)) {
        printf("队列已满，无法入队\n");
        return false;
    }
    q->subject[q->rear] = subject;
    q->rear = (q->rear + 1) % MAX_SUBJECT_NUM;
    return true;
}

// 出队操作
bool dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("队列为空，无法出队\n");
        return false;
    }
    q->front = (q->front + 1) % MAX_SUBJECT_NUM;
    return true;
}

// 获取队首元素
failSubject first(Queue *q) {
    return q->subject[q->front];
}