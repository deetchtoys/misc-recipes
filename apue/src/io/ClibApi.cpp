#include "ClibApi.h"

#include <cstdio>
#include <wchar.h>

int ClibApi::fwideClib(FILE *fp, int mode)
{
    return fwide(fp, mode);
}

void ClibApi::setbufClib(FILE *fp, char *buf)
{
    return setbuf(fp, buf);
}

int ClibApi::setvbufClib(FILE *fp, char *buf, int mode, size_t size)
{
    return setvbuf(fp, buf, mode, size);
}

int ClibApi::fflushClib(FILE *fp)
{
    return fflush(fp);
}

FILE *ClibApi::fopenClib(const char *pathname, const char *type)
{
    return fopen(pathname, type);
}

FILE *ClibApi::freopenClib(const char *pathname, const char *type, FILE *fp)
{
    return freopen(pathname, type, fp);
}

FILE *ClibApi::fdopenClib(int fd, const char *type)
{
    return fdopen(fd, type);
}

int ClibApi::fcloseClib(FILE *fp)
{
    return fclose(fp);
}
