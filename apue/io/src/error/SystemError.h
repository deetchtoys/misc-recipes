#ifndef ERROR_H_
#define ERROR_H_

#include <string>

#define ERROR_PREFIX __FILE__, __LINE__, __TIME__

class SystemError
{
  public:
    void printErrMsg(const char *fileName, int lineNum, const char *time);
};

class SystemException
{

};

#endif

