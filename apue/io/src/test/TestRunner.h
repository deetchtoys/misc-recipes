#ifndef TEST_RUNNER_H_
#define TEST_RUNNER_H_

#include "../error/SystemError.h"

class TestRunner
{
  public:
    TestRunner()
    {
        _systemError = SystemError();
    }

    void printErrMsg(const char *fileName, int lineNum, const char *time)
    {
        _systemError.printErrMsg(fileName, lineNum, time);
    }

    int run(int argc, char **argv);
  private:
    SystemError _systemError;
};






#endif
