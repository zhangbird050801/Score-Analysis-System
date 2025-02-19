#include "interface/interface.h"

int nowUser = -1;

static HANDLE handler[] = {sortInterface, analyzeInterface, searchInterface, scoreInterface, modifyInterface};

void userInterface() {
    makeInterface(USER, handler);
}