#include "tools/hint.h"
#include "interface/interface.h"
#include <unistd.h>

int main()
{
    welcomeMessage(); // 初始界面信息

    // 界面加载
    loadingMessage();

    // 从文件中加载数据
    loadUser();
    loadSubjects();
    loadMajor();
    loadStudent();

    sleep(1);

    loadingSuccess();
    
     mainInterface(); // 主交互界面

   
    
    // printStudentByMajor("M00001");

    // outUser();
    // outStudent();
    
    exitMessage(); // 退出信息


    return 0;
}