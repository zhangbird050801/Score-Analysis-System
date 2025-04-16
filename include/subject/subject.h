#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "config.h"

typedef struct {
    char id[MAX_ID_LENGTH];          // 课程编号
    char name[MAX_NAME_LENGTH];      // 课程名称
    double credit;                   // 课程学分
}Subject;

void loadSubjects();
void printSubject();
int idToidxOfSub(char *id);
char* getSubjectByIdx(char *id);
double getCreditByIdx(char *id);

#endif