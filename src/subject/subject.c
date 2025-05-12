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

/**
 * @brief 转换学科编号为对应下标
 * @param id:学科编号
 */
int idToidxOfSub(char *id){
    int res = 0;
    for(int i = 1; i < strlen(id);i++){
        res = res * 10 +(id[i] - '0');
    }
    return res - 1;
}

/**
 * @brief 将学科编号替换为学科名
 * @param id:学科编号
 */
char* getSubjectByIdx(char *id){
    int idx = idToidxOfSub(id);
    return subjects[idx].name;
}

/**
 * @brief 获取学科学分
 */
double getCreditByIdx(char *id){
    int idx = idToidxOfSub(id);
    return subjects[idx].credit;
}

