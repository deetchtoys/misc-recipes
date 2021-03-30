#include "SystemError.h"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <errno.h>
#include <sstream>

void SystemError::printErrMsg(const char *fileName, int lineNum, const char *time)
{
    std::stringstream ss;
    ss << time << " --- " << fileName << ":" << lineNum;
    std::perror(ss.str().c_str());
}
