#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "menu/menu.h"
#include "tools/color.h"
#include "tools/hint.h"
#include "tools/info.h"
#include "config.h"
#include "user/user.h"
#include "student/student.h"
#include "major/major.h"
#include "subject/subject.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern int nowUser;

typedef void (*HANDLE)(void); // 函数指针

void makeInterface(Menu type, HANDLE handler[]);

/* mainInterface */
void mainInterface();
void userLogin();
void adminLogin();
void userLoginSuccess(char *username);
void getName(char* name);
void getPassword(char* password);
void tryAgain(char *username, char *password, int cnt);
void adminLoginSuccess();

/* userInterface */
void userInterface();

/* adminInterface */
void adminLogin();

/* sortInterface */
void sortInterface();

/* analyzeInterface */
void analyzeInterface();

/* searchInterface */
void searchInterface();
void searchById();

/* scoreInterface */
void scoreInterface();

/* modifyInterface */
void modifyInterface();

#endif