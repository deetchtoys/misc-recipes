#include "IoTest.h"
#include "../io/UnixFileApi.h"
#include "../error/SystemError.h"
#include "../io/ClibApi.h"
#include <sys/stat.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/time.h>

using std::cout;
using std::endl;

UnixFileApi *fileBase = new UnixFileApi();
SystemError *systemError = new SystemError();

int testCURD(int argc, char *argv[])
{
    int fd = fileBase->openFile("./orgin.txt", O_RDWR | O_CREAT, RWRWRW);
    if (fd == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
        return -1;
    }


    std::string buffStr = "==== 标题 ====";
    ssize_t result = fileBase->writeFile(buffStr);
    if (result == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
        return -1;
    }

    fd = fileBase->closeFile();
    if (fd == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
        return -1;
    }

    return 0;
}

int fcntlTest(int argc, char *argv[])
{
    return 0;
}

int ioctlTest(int argc, char *argv[])
{
    return 0;
}

int statTest(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        struct stat buf;
        std::string ptr;
        int ret = fileBase->lstatFile(argv[1], &buf);
        if (ret == -1)
        {
            systemError->printErrMsg(ERROR_PREFIX);
            continue;
        }

        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        else if (S_ISDIR(buf.st_mode))
            ptr = "dir";
        else if (S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";

        std::cout << ptr << std::endl;
    }

    return 0;
}

int accessTest(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        struct stat buf;
        std::string ptr;
        int ret = fileBase->lstatFile(argv[i], &buf);
        if (ret == -1)
        {
            systemError->printErrMsg(ERROR_PREFIX);
            continue;
        }

        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        else if (S_ISDIR(buf.st_mode))
            ptr = "dir";
        else if (S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";

        std::cout << ptr << std::endl;
        std::cout << (fileBase->accessFile(argv[i], R_OK) == 0 ? "R_OK" : "NO R_OK") << std::endl;
        std::cout << (fileBase->accessFile(argv[i], W_OK) == 0 ? "W_OK" : "NO W_OK") << std::endl;
        std::cout << (fileBase->accessFile(argv[i], X_OK) == 0 ? "X_OK" : "NO X_OK") << std::endl;
    }

    return 0;
}

int futimensTest(int argc, char **argv)
{
    struct timespec times[2];
    int fd = fileBase->openFile("./wdq.txt", O_RDWR | O_CREAT, RWRWRW);
    if (fd == -1)
        systemError->printErrMsg(ERROR_PREFIX);
    else
    {
        fileBase->futimensFile(fd, times);
    }

    return 0;
}

int dirTree(int argc, char **argv)
{
    char curPath[255] = {0};
    char *retStr = fileBase->getcwdFile(curPath, 255);
    if (retStr == NULL)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << "currentPath:" << curPath << endl;
    }

    DIR *dir =  fileBase->opendirFile(argv[1]);
    if (dir == NULL)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        fileBase->seekdirFile(dir, 10);
        fileBase->rewinddirFile(dir);
        struct dirent *dirInfo;
        while ((dirInfo = fileBase->readdirFile(dir)) != NULL)
        {
            cout << "d_in:" <<dirInfo->d_ino << endl
                 << "d_name:" <<dirInfo->d_name << endl
                 << "d_off:" <<dirInfo->d_off << endl
                 << "d_reclen:" << dirInfo->d_reclen << endl
                 << "d_type:" << dirInfo->d_type << endl;
            cout << "============================================" << endl;
        }
    }

    return 0;
}

int clibTest(int argc, char **argv)
{
    ClibApi *clibApi = new ClibApi();
    FILE *fp = clibApi->fopenClib("./wdq.txt", "a+");
    cout << clibApi->fwideClib(fp, 0) << endl;

    return 0;
}

int formatPrint(int argc, char **argv)
{
    printf("%010d\n", 1234567);
    return 0;
}

int testTmpFile(int argc, char **argv)
{
    char name[20];
    // cout << tmpnam(NULL) << endl;
    // tmpnam(name);
    cout << name << endl;
    FILE *fp = tmpfile();
    if (fp == 0)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    fputs("hello", fp);

    return 0;
}

int testTmpDir(int argc, char **argv)
{
    char name[] = "wdqXXXXXX";
    char *dirName = mkdtemp(name);
    if (!dirName)
    {
        cout << "error" << endl;
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << "success" << endl;
        cout << dirName << endl;
        cout << name << endl;
        char fileName[] = "wangwangwangXXXXXXXXX";
        int fd = mkstemp(fileName);
        if (fd == -1)
        {
            systemError->printErrMsg(ERROR_PREFIX);
        }
    }


    return 0;
}

int testMemstream(int argc, char **argv)
{
    const int BUFFER_SIZE = 10;
    char buf[BUFFER_SIZE];
    memset(buf, 'a', BUFFER_SIZE);
    buf[BUFFER_SIZE - 1] = '\0';
    printf("org %s\n", buf);
    FILE *fp = fmemopen(buf, BUFFER_SIZE, "w+");
    if (!fp)
    {
        systemError->printErrMsg(ERROR_PREFIX);
        return 0;
    }

    fprintf(fp, "hello");
    printf("buf: %s\n", buf);
    // fflush(fp);
    // printf("after fflush buf: %s\n", buf);
    fseek(fp, -2, SEEK_CUR);
    // rewind(fp);
    printf("after fseek buf: %s\n", buf);
    printf("fgetc %c\n",fgetc(fp));

    return 0;
}

int testPasswd(int argc, char **argv)
{
    // struct passwd *passInfo = getpwuid(1000);
    cout << "==================pw================" << endl;
    struct passwd *passInfo = getpwnam("root");
    if (!passInfo)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << passInfo->pw_dir << endl;
        cout << passInfo->pw_gecos << endl;
        cout << passInfo->pw_gid << endl;
        cout << passInfo->pw_name << endl;
        cout << passInfo->pw_passwd << endl;
        cout << passInfo->pw_shell << endl;
        cout << passInfo->pw_uid << endl;
    }

    cout << "####################################" << endl << endl;
    cout << "==================sp================" << endl;
    struct spwd *shadowPasswdInfo = getspnam("aidu37");
    if (!shadowPasswdInfo)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << shadowPasswdInfo->sp_expire << endl;
        cout << shadowPasswdInfo->sp_flag << endl;
        cout << shadowPasswdInfo->sp_inact << endl;
        cout << shadowPasswdInfo->sp_lstchg << endl;
        cout << shadowPasswdInfo->sp_max << endl;
        cout << shadowPasswdInfo->sp_min << endl;
        cout << shadowPasswdInfo->sp_namp << endl;
        cout << shadowPasswdInfo->sp_pwdp << endl;
        cout << shadowPasswdInfo->sp_warn << endl;
    }
    cout << "####################################" << endl << endl;
    cout << "==================gr================" << endl;
    // struct group *groupInfo = getgrgid();
    struct group *groupInfo = getgrnam("aidu37");
    if (!groupInfo)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << groupInfo->gr_gid << endl;
        cout << groupInfo->gr_name << endl;
        cout << groupInfo->gr_passwd << endl;
        if (groupInfo->gr_mem)
        {
            char **memArray = groupInfo->gr_mem;
            while (*memArray)
            {
                cout << *memArray++ << endl;
            }
        }
    }
    cout << "####################################" << endl << endl;
    cout << "==================groups================" << endl;

    gid_t groupList[10];
    int errId = getgroups(10, groupList);
    if (errId == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        for (int i = 0; i < errId; ++i)
        {
            cout << groupList[i] << endl;
        }
    }
    cout << "####################################" << endl << endl;

    cout << "==================uname================" << endl;
    struct utsname nameInfo;
    errId = uname(&nameInfo);
    if (errId == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << nameInfo.domainname << endl;
        cout << nameInfo.machine << endl;
        cout << nameInfo.nodename << endl;
        cout << nameInfo.release << endl;
        cout << nameInfo.sysname << endl;
        cout << nameInfo.version << endl;
        char hostName[65];
        memset(hostName, 0, 65);
        errId = gethostname(hostName, 65);
        if (errId == -1)
        {
            systemError->printErrMsg(ERROR_PREFIX);
        }
        else
        {
            cout << "hostname:" << hostName << endl;
        }
    }
    cout << "####################################" << endl << endl;

    return 0;
}


int testTime(int argc, char **argv)
{
    time_t currentTime;
    if (time(&currentTime) == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << "time():" << currentTime << endl;
    }
    struct timespec timespecInfo;
    if (clock_gettime(CLOCK_REALTIME, &timespecInfo) == -1)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << timespecInfo.tv_sec << "." << timespecInfo.tv_nsec << endl;
    }

    struct timeval timevalInfo;
    if (gettimeofday(&timevalInfo, NULL))
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        cout << timevalInfo.tv_sec << "." << timevalInfo.tv_usec << endl;
    }

    struct tm tmInfo;
    struct tm tmInfo1;
    struct tm * systmInfo = gmtime(&currentTime);
    if (!systmInfo)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        memcpy(&tmInfo, systmInfo, sizeof(struct tm));
        systmInfo = localtime(&currentTime);
        if (!systmInfo)
        {
            systemError->printErrMsg(ERROR_PREFIX);
        }
        else
        {
            memcpy(&tmInfo1, systmInfo, sizeof(struct tm));
            cout << tmInfo.tm_gmtoff << "====" << tmInfo1.tm_gmtoff << endl;
            cout << tmInfo.tm_hour << "====" << tmInfo1.tm_hour << endl;
            cout << tmInfo.tm_isdst << "====" << tmInfo1.tm_isdst << endl;
            cout << tmInfo.tm_mday << "====" << tmInfo1.tm_mday << endl;
            cout << tmInfo.tm_min << "====" << tmInfo1.tm_min << endl;
            cout << tmInfo.tm_mon << "====" << tmInfo1.tm_mon << endl;
            cout << tmInfo.tm_sec << "====" << tmInfo1.tm_sec << endl;
            cout << tmInfo.tm_wday << "====" << tmInfo1.tm_wday << endl;
            cout << tmInfo.tm_yday << "====" << tmInfo1.tm_yday << endl;
            cout << tmInfo.tm_year << "====" << tmInfo1.tm_year << endl;
            cout << tmInfo.tm_zone << "====" << tmInfo1.tm_zone << endl;
        }
    }

    return 0;
}

int testEnv(int argc, char **argv)
{
    char envName[] = "wdq=hello";
    if (putenv(envName) != 0)
    {
        systemError->printErrMsg(ERROR_PREFIX);
    }
    else
    {
        envName[4] = '#';
        char *envWdqValue = getenv("wdq");
        if (!envWdqValue)
        {
            systemError->printErrMsg(ERROR_PREFIX);
        }
        else
        {
            cout << envWdqValue << endl;
        }
    }
    return 0;
}

#define HELLO 10
#define hoho(name) haha(#name, name)

void haha(const std::string &name, int value)
{
    cout << name << ":" << value << endl;
}

int testMicro(int argc, char **argv)
{
    hoho(HELLO);
    return 0;
}

int IoTest::test(int argc, char **argv)
{
    return testMicro(argc, argv);
}
