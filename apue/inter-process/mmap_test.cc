#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <cstring>

#include <iostream>

using namespace std;

int main()
{
  long page_size = sysconf(_SC_PAGESIZE);
  cout << "page_size: " << page_size << endl;
  int fdin = open("./wdq-in.txt", O_RDWR);
  if (fdin < 0)
  {
    cout << "open fdin file failed" << endl;
    return -1;
  }

  int fdout = open("./wdq-out.txt",
                   O_RDWR | O_CREAT,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (fdout < 0)
  {
    cout << "open fdout file failed" << endl;
    return -1;
  }

  struct stat sbuf;
  if (fstat(fdin, &sbuf) < 0)
  {
    return -1;
  }

  if (ftruncate(fdout, sbuf.st_size) < 0)
  {
    return -1;
  }

  int copy_incr = 1024 * 1024 * 1024;
  off_t fsz = 0;
  int copy_size = 0;
  void *src = nullptr;
  void *dst = nullptr;
  cout << "before task" << endl;
  sleep(15);
  cout << "start task" << endl;
  int index = 0;
  while (fsz < sbuf.st_size)
  {
    if ((sbuf.st_size - fsz) > copy_incr)
    {
      copy_size = copy_incr;
    }
    else
    {
      copy_size = sbuf.st_size - fsz;
    }
    cout << "copy_size: " << copy_size << endl;
    if ((src = mmap(0, copy_size, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
    {
      cout << "mmap failed" << endl;
      return -1;
    }
    cout << *((char *)src + index) << endl;
    // if ((dst = mmap(0, copy_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
    // {
    //   cout << "mmap failed" << endl;
    //   return -1;
    // }

    // memcpy(dst, src, copy_size);
    sleep(5);
    munmap(src, copy_size);
    // munmap(dst, copy_size);
    // fsz += copy_size;
    index += page_size;
  }
  cout << "task end" << endl;
  sleep(10);
  return 0;
}
