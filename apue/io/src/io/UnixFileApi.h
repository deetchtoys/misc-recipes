#ifndef UNIX_FILE_API_H_
#define UNIX_FILE_API_H_

#include <string>
#include <fcntl.h>
#include <dirent.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

class UnixFileApi
{
  public:
    UnixFileApi();
    int openFile(const std::string filePath, int oflag, mode_t mode);
    size_t writeFile(const std::string &buff);
    size_t writeFile(const char *buffer, int buffSize);
    size_t readFile(char *buffer, const int buffSize);
    int closeFile();
    int fsyncFile();
    int fdatasyncFile();
    void syncFile();
    int fcntlFile(int fd, int cmd, ...);
    int ioctlFile(int fd, int request, ...);
    int statFile(const char *pathname, struct stat *buf);
    int fstatFile(int fd, struct stat *buf);
    int lstatFile(const char *pathname, struct stat *buf);
    int fstatatFile(int fd, const char *pathname, struct stat *buf, int flag);
    int accessFile(const char *pathname, int mode);
    int faccessatFile(int fd, const char *pathname, int mode, int flag);
    int futimensFile(int fd, const struct timespec times[2]);
    int utimensatFile(int fd, const struct timespec times[2]);
    DIR *opendirFile(const char *pathname);
    DIR *fdopendirFile(int fd);
    struct dirent *readdirFile(DIR *dp);
    void rewinddirFile(DIR *dp);
    int closedirFile(DIR *dp);
    long telldirFile(DIR *dp);
    void seekdirFile(DIR *dp, long loc);
    char *getcwdFile(char *buf, size_t size);
  private:
    int _fd;
};

#endif

