#include "tools/hint.h"
#include "tools/color.h"
#include <stdio.h>

static const char* BANNER = "\
\t   _____                                         _           _        _____           _                 _      \n\
\t  / ____|                      /\\               | |         (_)      / ____|         | |               | |     \n\
\t | (___   ___ ___  _ __ ___   /  \\   _ __   __ _| |_   _ ___ _ ___  | (___  _   _ ___| |_ ___ _ __ ___ | |     \n\
\t  \\___ \\ / __/ _ \\| '__/ _ \\ / /\\ \\ | '_ \\ / _` | | | | / __| / __|  \\___ \\| | | / __| __/ _ | '_ ` _ \\| |      \n\
\t  ____) | (_| (_) | | |  __// ____ \\| | | | (_| | | |_| \\__ | \\__ \\  ____) | |_| \\__ | ||  __| | | | | |_|      \n\
\t |_____/ \\___\\___/|_|  \\___/_/    \\_|_| |_|\\__,_|_|\\__, |___|_|___/ |_____/ \\__, |___/\\__\\___|_| |_| |_(_)       \n\
\t                                                    __/ |                    __/ |                \n\
\t                                                   |___/                    |___/                    \n\
";

static const char* GOODBYE = "\
\t                                                                            ,---,  \n\
\t                                                                         ,`--.' |  \n\
\t  ,----..                                      ,---,.                    |   :  :  \n\
\t /   /   \\                            ,---,  ,'  .'  \\                   '   '  ;  \n\
\t|   :     :    ,---.     ,---.      ,---.'|,---.' .' |                   |   |  |  \n\
\t.   |  ;. /   '   ,'\\   '   ,'\\     |   | :|   |  |: |                   '   :  ;  \n\
\t.   ; /--`   /   /   | /   /   |    |   | |:   :  :  /     .--,   ,---.  |   |  '  \n\
\t;   | ;  __ .   ; ,. :.   ; ,. :  ,--.__| |:   |    ;    /_ ./|  /     \\ '   :  |  \n\
\t|   : |.' .''   | |: :'   | |: : /   ,'   ||   :     \\, ' , ' : /    /  |;   |  ;  \n\
\t.   | '_.' :'   | .; :'   | .; :.   '  /  ||   |   . /___/ \\: |.    ' / |`---'. |  \n\
\t'   ; : \\  ||   :    ||   :    |'   ; |:  |'   :  '; |.  \\  ' |'   ;   /| `--..`;  \n\
\t'   | '/  .' \\   \\  / \\   \\  / |   | '/  '|   |  | ;  \\  ;   :'   |  / |.--,_     \n\
\t|   :    /    `----'    `----'  |   :    :||   :   /    \\  \\  ;|   :    ||    |`.  \n\
\t \\   \\ .'                        \\   \\  /  |   | ,'      :  \\  \\   \\  / `-- -`, ; \n\
\t  `---`                           `----'   `----'         \\  ' ; `----'    '---`\"  \n\
\t                                                           `--`                    \n\
";

static const char* FAILURE = "\t\t*** 操作失败,请重新再试! ***";
static const char* EXIT = "\t\t\t\t\t*** 退出成功! ***";
static const char* LOGINFAILURE = "\t\t*** 登陆失败，请重新再试！***";
static const char* LOGINSUCCESS = "\n\t\t*** 登陆成功！***";
static const char* DESIGNERS = "Designer: Zhang Xinyi, Yang Wenrong.";
static const char* NEXTTIME = "\t\t\t\t       *** 欢迎下次再来！***";
static const char* LOADING = "\n\t\t***** 加载中 *****";
static const char* LOADINGSUCCESS = "\t\t*** 加载成功! ***";
static const char* LOGINOUT = "\t\t*** 注销成功！***";

void welcomeMessage() 
{
    printf("\n%s%sWelcome to%s\n", BOLD, FRONT_RED, RESET);
    printf("%s%s%s%s\n", FRONT_BLUE, BOLD, BANNER, RESET);
    printf("%s%s%s\n\n", FRONT_PURPLR, DESIGNERS, RESET);
}

void exitMessage()
{
    printf("%s%s%s%s\n", BOLD, FRONT_RED, EXIT, RESET);
    printf("\n%s%s%s%s\n", FRONT_RED, BOLD, GOODBYE, RESET);
    printf("%s%s%s\n", FRONT_YELLOW, NEXTTIME, RESET);
}