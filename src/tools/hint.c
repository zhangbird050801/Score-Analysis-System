#include "tools/hint.h"
#include "tools/color.h"
#include "tools/info.h"

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
static const char* LOGINFAILURE = "\t\t*** 登录失败，请重新再试！***";
static const char* LOGINSUCCESS = "\n\t\t*** 登录成功！***";
static const char* DESIGNERS = "Designer: Zhang Xinyi, Yang Wenrong.";
static const char* NEXTTIME = "\t\t\t\t       *** 欢迎下次再来！***";
static const char* LOADING = "\n\t\t***** 加载中 *****";
static const char* LOADINGSUCCESS = "\t\t*** 加载成功! ***";
static const char* LOGINOUT = "\t\t*** 注销成功！***";
static const char* ERRO_FINDING_USER = "\t\t***** 未找到该用户！*****";
static const char* ERRO_FINDING_STUDENT = "\t\t***** 未找到该学生！*****";
static const char* ADD_STUDENT_SUCCESS = "\t\t***** 添加学生成功！*****";
static const char* ADD_STUDENT_ERROR = "\t***** 该学号已存在，添加失败！*****";
static const char* MODIFY_PASSWORD_ERROR = "\t\t***两次输入的新密码不一致!***";
static const char* MODIFY_PASSWORD_SUCCESS = "\t\t*****修改密码成功！*****";
static const char* SYSTEM_LOCAL_DATE_TIME = "当前系统时间为: ";
static const char* ADD_USER_SUCCESS = "\t\t***** 添加用户成功！*****";
static const char* ADD_USER_ERROR = "\t\t** 该用户名已存在, 添加失败！**";
denglu
static const char* INFO = "\
+============+======+============+========+======+==============+==========+==========+==============+================+\n\
|    学号    | 姓名 |     专业   |  年级  | 班级 | 平均学分绩点 | 加权分数 | 学科数目 | 已获得总学分 | 不及格科目数量 |\n\
+============+======+============+========+======+==============+==========+==========+==============+================+\n\
";

void welcomeMessage() {
    printf("\n%s%sWelcome to%s\n", BOLD, FRONT_RED, RESET);
    printf("%s%s%s%s\n", FRONT_BLUE, BOLD, BANNER, RESET);
    printf("%s%s%s\n\n", FRONT_PURPLR, DESIGNERS, RESET);
    printf("%s%s%s%s%s%s%s\n\n", FRONT_YELLOW, SYSTEM_LOCAL_DATE_TIME, RESET, FRONT_BLUE, UNDERLINE, getTime(), RESET);
}

void exitMessage() {
    printf("%s%s%s%s\n", BOLD, FRONT_RED, EXIT, RESET);
    printf("\n%s%s%s%s\n", FRONT_RED, BOLD, GOODBYE, RESET);
    printf("%s%s%s\n", FRONT_YELLOW, NEXTTIME, RESET);
}

void failureMessage() {printf("%s%s%s\n\n", FRONT_RED, FAILURE, RESET);}

void loadingMessage(){printf("%s%s%s%s\n\n", BOLD, TWINKLING, LOADING, RESET);}

void loadingSuccess(){printf("%s%s%s%s\n\n", BOLD, FRONT_RED, LOADINGSUCCESS, RESET);}

void loginFailureMessage(){printf("%s%s%s%s\n\n", BOLD, FRONT_RED, LOGINFAILURE, RESET);}

void loginSuccessMessage(){printf("%s%s%s%s\n\n", BOLD, FRONT_BLUE, LOGINSUCCESS, RESET);}

void errorFindingUser(){printf("%s%s%s\n\n", FRONT_RED, ERRO_FINDING_USER, RESET);}

void errorFindingStudent(){printf("\n%s%s%s\n\n", FRONT_RED, ERRO_FINDING_STUDENT, RESET);}

void addStudentSuccess(){printf("\n%s%s%s\n\n", FRONT_PURPLR, ADD_STUDENT_SUCCESS, RESET);}

void addStudentError(){printf("\n%s%s%s\n\n", FRONT_RED, ADD_STUDENT_ERROR, RESET);}

void modifyPasswordError(){printf("\n%s%s%s\n\n", FRONT_RED, MODIFY_PASSWORD_ERROR, RESET);}

void modifyPasswordSuccess(){printf("\n%s%s%s%s\n\n",BOLD,FRONT_GREEN,MODIFY_PASSWORD_SUCCESS,RESET);}

void addUserSuccess(){printf("\n%s%s%s\n\n", FRONT_PURPLR, ADD_USER_SUCCESS, RESET);}

void addUserError(){printf("\n%s%s%s\n\n", FRONT_RED, ADD_USER_ERROR, RESET);}

void printInfo(){printf("\n%s%s%s%s", BOLD, FRONT_BLUE, INFO, RESET);}