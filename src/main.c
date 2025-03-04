#include "tools/hint.h"
#include "interface/interface.h"
#include <unistd.h>

int main()
{
    // 从文件中加载数据
    // loadUser();
    // loadStudent();
    loadSubjects();

    welcomeMessage(); // 初始界面信息

    // 界面加载
    loadingMessage();
    sleep(1);
    loadingSuccess();

    // mainInterface(); // 主交互界面
    printSubject();

    // 输出文件
    // outUser();

    exitMessage(); // 退出信息

    return 0;
}