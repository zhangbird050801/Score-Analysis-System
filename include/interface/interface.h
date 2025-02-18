#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "menu/menu.h"
#include "tools/color.h"
#include "tools/hint.h"
#include "tools/info.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern int nowUser;

typedef void (*HANDLE)(void); // 定义函数指针

void makeInterface(Menu type, HANDLE handler[]);

/* mainInterface */
void mainInterface();
void userLogin();
void userLoginSuccess(char *username);
void getName(char* name);
void getPassword(char* password);
void tryAgain(char *username, char *password, int cnt);

/* userInterface */


#endif