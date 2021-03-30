#ifndef SHARED_MEMORY_MAPPER_H_
#define SHARED_MEMORY_MAPPER_H_

#include <sys/mman.h>

class SharedMemoryMapper
{
 public:
  void *Mmap(void *addr, size_t len, int prot, int flag, int fd, off_t off)
  {
    return mmap(addr, len, prot, flag, fd, off);
  }

  int Mprotect(void *addr, size_t len, int prot)
  {
    return mprotect(addr, len, prot);
  }

  int Msync(void *addr, size_t len, int flags)
  {
    return msync(addr, len, flags);
  }

  int Munmap(void *addr, size_t len)
  {
    return Munmap(addr, len);
  }
};


#endif
