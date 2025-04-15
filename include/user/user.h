#ifndef _USER_H_
#define _USER_H_

#include "config.h"

typedef struct{
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
}User;

User *getUser(int idx);

void loadUser();
void outUser();
int check(char *name, char *pwd);
int searchByUserName(char *name);
int searchByUserId(char *id);
void addNewUser(char* name,char* password);

#endif