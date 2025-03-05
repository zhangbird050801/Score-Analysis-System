#include "interface/interface.h"

static const char* FILEPATH = "src/Data/Major.txt";
static Major majors[MAX_MAJOR_NUM];   
static int totalMajor = 0; 

/**
 * @brief 加载专业信息
 */
void loadMajor() {
    FILE *maj = fopen(FILEPATH,"r");
    while(fscanf(maj,"%s%s",majors[totalMajor].id,\
        majors[totalMajor].name) != EOF){
            totalMajor ++;
        }
    fclose(maj);
}

/**
 * @brief 打印专业信息
 */
void printMajor(){
    int i ;
    for(i = 0;i < totalMajor;i++){
        printf("%s %s\n",majors[i].id,majors[i].name);
    }
}

/**
 * @brief 转换专业编号为对应下标
 * @param id:专业编号
 */
int idToIdx(char* id) {
    int res = 0;
    for(int i = 1; i < strlen(id); i ++) {
        res = res * 10 + (id[i] - '0');
    }
    return res - 1;
}

/**
 * @brief 将专业编号替换为专业名
 * @param id：专业编号
 */
char* getMajorByIdx(char* id) {
    int idx = idToIdx(id);
    return majors[idx].name;
}