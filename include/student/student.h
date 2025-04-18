#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "config.h"
#include <math.h>  // 用于fabs()函数
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char id[MAX_ID_LENGTH];
    double score;  
} score;

typedef struct student {
    char id[MAX_ID_LENGTH];          // 学号      
    char name[MAX_NAME_LENGTH];      // 姓名
    char major[MAX_ID_LENGTH];       // 专业
    int grade;                       // 年级
    int classId;                     // 班级
    int subjectNum;                  // 选修科目数
    score scores[MAX_SUBJECT_NUM];   // 选修科目成绩
    struct student *next;            // 链表指针
} student;

unsigned int hash(char *str);
void loadStudent();
void outStudent();
void addStudent(student *stu);
void printStudent(student *stu);
student *searchStudentById(char *id);
void searchStudentByName(char *name);
double countGPA(double score);
double countAverageGPA(student *stu);
double getWAM(student *stu);

int compare(const void *a, const void *b);
void printStudentByClass(const char *majorId,int grade,int class);
void printStudentByMajor(const char *majorId);
student **getStudentByMajor(const char *majorId, int *count);
student **getStudentByClass(const char *majorId, int grade, int class, int *count);
void quickSort(void *base, int left, int right, size_t size, int (*cmp)(const void *, const void *));

#endif