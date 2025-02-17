#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Menu/menu.h"
#include "tools/color.h"
#include "tools/hint.h"
#include "tools/info.h"
#include <stdlib.h>

typedef void (*HANDLE)(void); // 定义函数指针

void MAKE_Interface(Menu type, HANDLE handler[]);

/* MAIN_Interface */
void MAIN_Interface();

#endif