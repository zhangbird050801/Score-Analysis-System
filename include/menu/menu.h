#ifndef _MENU_H_
#define _MENU_H_

typedef enum {MAIN, USER, ADMIN, SORT, ANALYZE, SEARCH, SCORE, MODIFY} Menu;

extern const int optionNumber[];

int menu(Menu type);

#endif