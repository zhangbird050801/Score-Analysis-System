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