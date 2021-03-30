#ifndef CLIB_API_H_
#define CLIB_API_H_

#include <stdio.h>

class ClibApi
{
  public:
    int fwideClib(FILE *fp, int mode);
    void setbufClib(FILE *fp, char *buf);
    int setvbufClib(FILE *fp, char *buf, int mode, size_t size);
    int fflushClib(FILE *fp);
    FILE *fopenClib(const char *pathname, const char *type);
    FILE *freopenClib(const char *pathname, const char *type, FILE *fp);
    FILE *fdopenClib(int fd, const char *type);
    int fcloseClib(FILE *fp);
};


#endif
