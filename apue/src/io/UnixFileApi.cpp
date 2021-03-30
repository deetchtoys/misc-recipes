#include "UnixFileApi.h"

#include <iostream>
#include <string>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

UnixFileApi::UnixFileApi(){}

int UnixFileApi::openFile(const std::string filePath, int oflag, mode_t mode)
{
    int fd = open(filePath.c_str(), oflag, mode);
    if (fd != -1)
        _fd = fd;

    return fd;
}


size_t UnixFileApi::writeFile(const std::string &buffer)
{
    size_t count = write(_fd, buffer.c_str(), buffer.length());
    return count;
}

size_t UnixFileApi::writeFile(const char *buffer, int bufferSize)
{
    size_t count = write(_fd, buffer, bufferSize);
    return count;
}

size_t UnixFileApi::readFile(char *buffer, const int bufferSize)
{
    size_t count = read(_fd, buffer, bufferSize);
    return count;
}

int UnixFileApi::closeFile()
{
    int ret = close(_fd);
    return ret;
}


int UnixFileApi::fsyncFile()
{
    return fsync(_fd);
}

int UnixFileApi::fdatasyncFile()
{
    return fdatasync(_fd);
}

void UnixFileApi::syncFile()
{
    sync();
}

int UnixFileApi::fcntlFile(int fd, int cmd, ...)
{
    return 0;
}

int UnixFileApi::ioctlFile(int fd, int request, ...)
{
    return 0;
}

int UnixFileApi::statFile(const char *pathname, struct stat *buf)
{
    return stat(pathname, buf);
}

int UnixFileApi::fstatFile(int fd, struct stat *buf)
{
    return fstat(fd, buf);
}

int UnixFileApi::lstatFile(const char *pathname, struct stat *buf)
{
    return lstat(pathname, buf);
}

int UnixFileApi::fstatatFile(int fd, const char *pathname, struct stat *buf, int flag)
{
    return 0;
}

int UnixFileApi::accessFile(const char *pathname, int mode)
{
    return access(pathname, mode);
}

int UnixFileApi::faccessatFile(int fd, const char *pathname, int mode, int flag)
{
    return faccessat(fd, pathname, mode, flag);
}

int UnixFileApi::futimensFile(int fd, const struct timespec times[2])
{
    return futimens(fd, times);
}

int UnixFileApi::utimensatFile(int fd, const struct timespec times[2])
{
    return 0;
}

DIR *UnixFileApi::opendirFile(const char *pathname)
{
    return opendir(pathname);
}

DIR *UnixFileApi::fdopendirFile(int fd)
{
    return fdopendir(fd);
}

struct dirent *UnixFileApi::readdirFile(DIR *dp)
{
    return readdir(dp);
}

void UnixFileApi::rewinddirFile(DIR *dp)
{
    return rewinddir(dp);
}

int UnixFileApi::closedirFile(DIR *dp)
{
    return closedir(dp);
}

long UnixFileApi::telldirFile(DIR *dp)
{
    return telldir(dp);
}

void UnixFileApi::seekdirFile(DIR *dp, long loc)
{
    return seekdir(dp, loc);
}

char *UnixFileApi::getcwdFile(char *buf, size_t size)
{
    return getcwd(buf, size);
}
