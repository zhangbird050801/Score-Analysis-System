#include <stdio.h>
#include <string.h>
#include "tools/hint.h"

void generateId(char* s, char type);
char* getTime();

int getUTF8CharLength(const char* str);
int splitUTF8String(const char* str, char chars[][8], int maxChars);