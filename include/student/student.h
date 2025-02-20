#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "config.h"

typedef struct {
    char id[MAX_ID_LENGTH];
    double score;
} score;

typedef struct student {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char major[MAX_ID_LENGTH];
    int grade;
    int classId;
    int subjectNum;
    score scores[MAX_SUBJECT_NUM];
    
    struct student *next;
} student;

void loadStudent();
void addStudent(student *stu);
void printStudent(student *stu);
student *searchByStudentId(char *id);

#endif