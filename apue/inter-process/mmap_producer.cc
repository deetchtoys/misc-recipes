#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <cstring>

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  long page_size = sysconf(_SC_PAGESIZE);
  cout << "page_size: " << page_size << endl;
  int fdin = open("./nums.txt", O_RDWR);
  if (fdin < 0)
  {
    cout << "open fdin file failed" << endl;
    return -1;
  }

  void *src = nullptr;
  cout << "before task" << endl;
  sleep(15);
  cout << "start task" << endl;
  int mapp_size = 4;
  if ((src = mmap(0, mapp_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdin, 0)) == MAP_FAILED)
  {
    cout << "mmap failed" << endl;
    return -1;
  }
  int index = 0;
  while (index < 100)
  {
    cout << "value: " << *(int *)src << endl;
    *(int *)src = *(int *)src + 1;
    ++index;
    sleep(1);
  }
  cout << "finally value: " << *(int *)src << endl;
  munmap(src, mapp_size);
  cout << "task end" << endl;
  sleep(10);
  return 0;
}
