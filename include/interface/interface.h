#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "menu/menu.h"
#include "tools/color.h"
#include "tools/hint.h"
#include "tools/info.h"
#include "tools/printHelp.h"
#include "config.h"
#include "user/user.h"
#include "student/student.h"
#include "major/major.h"
#include "subject/subject.h"
#include "queue/queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

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
void adminInterface();
void adminLogin();
void addUser();

/* sortInterface */
void sortInterface();
void sortByGrade();
void sortByClass();

/* analyzeInterface */
void analyzeInterface();
void analyzeGrade();
void analyzeClass();
double max(double a, double b);
double min(double a, double b);
void printScoreAnalysis(const char *subjectName, ScoreAnalysis *analysis);
void analyzeScores(double *scores, int count, ScoreAnalysis *result);
void printAnalysisHeader(const char *majorName, int classId);

/* searchInterface */
void searchInterface();
void searchById();
void searchByName();

/* scoreInterface */
void scoreInterface();
void inputScore();
void modifyScore();

/* modifyInterface */
void modifyInterface();
void modifyPassword();

#endif