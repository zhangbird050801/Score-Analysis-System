#include "interface/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

static HANDLE handler[] = {};

void MAKE_Interface(Menu type, HANDLE handler[])
{
    int op = menu(type);
    while(op != optionNumber[type]) {
        handler[op - 1](); 
        op = menu(type);
    }
}

void MAIN_Interface() {MAKE_Interface(MAIN, handler);}