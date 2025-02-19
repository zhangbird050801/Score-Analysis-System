#ifndef _MAJOR_H_
#define _MAJOR_H_

#include "config.h"

typedef struct  
{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
} major;

void loadMajor();

#endif 