#include "TestRunner.h"

#include "../common/CommonFeature.h"
#include "../container/ContainerFeature.h"
#include "../commonUtil/commonUtil.h"
#include "../thread/threadFeature.h"
#include "../boost_cases/BoostFeature.h"
#include "../ioutils/IoFeature.h"



int TestRunner::run(int argc, char **argv)
{
    return IoFeature().examples(argc, argv);
}
