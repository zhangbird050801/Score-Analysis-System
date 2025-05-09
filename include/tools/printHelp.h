#ifndef _PRINTHELP_H_
#define _PRINTHELP_H_
#define _XOPEN_SOURCE 700 

#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

int get_display_width(const char *str);
void print_centered(const char *str, int column_width);

#endif