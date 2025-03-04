#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "config.h"

typedef struct {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    double credit;
} subject;

void loadSubjects();
void printSubject();

#endif