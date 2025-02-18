#include "tools/hint.h"
#include "interface/interface.h"
#include <unistd.h>

int main()
{
    // 从文件中加载数据

    welcomeMessage(); // 初始界面信息

    // 界面加载
    loadingMessage();
    sleep(1);
    loadingSuccess();

    MAIN_Interface(); // 主交互界面

    // 输出文件
    

    exitMessage(); // 退出信息

    return 0;
}