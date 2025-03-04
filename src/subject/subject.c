#include "interface/interface.h"

//存储subject信息的位置
static const char* FILEPATH = "src/Data/Subject.txt";
static subject sub[MAX_SUBJECT_NUM];   //静态的指针数组，用于存储指向 subject 结构体的指针
static int totalSubject = 0; 

// TODO: 从文件中读取 subject
void loadSubjects() {
    FILE *file = fopen(FILEPATH, "r");//read
    while(fscanf(file,"%s %s %lf",sub[totalSubject].id,sub[totalSubject].name, &sub[totalSubject].credit)){
            // printf("%s%s%.2lf",sub[totalSubject].id,sub[totalSubject].name,sub[totalSubject].credit);
            totalSubject++;
        }
    fclose(file);
}

void printSubject(){
    int i;
    for(i = 0 ; i < totalSubject ; i ++){
        printf("%s%s%.2lf\n",sub[i].id,sub[i].name,sub[i].credit);
    }
}