#include "interface/interface.h"

static const char* FILEPATH = "src/Data/Subject.txt";
static Subject subjects[MAX_SUBJECT_NUM];   
static int totalSubject = 0; 

/**
 * @brief 加载学科信息
 */
void loadSubjects() {
    FILE *ptr = fopen(FILEPATH, "r");

    while(fscanf(ptr, "%s%s%lf", subjects[totalSubject].id, subjects[totalSubject].name, \
        &subjects[totalSubject].credit) != EOF){
            totalSubject++;
        }

    fclose(ptr);
}

/**
 * @brief 打印学科信息
 */
void printSubject(){
    int i;
    for(i = 0 ; i < totalSubject ; i ++){
        printf("%s %s %.2lf\n", subjects[i].id, subjects[i].name, subjects[i].credit);
    }
}