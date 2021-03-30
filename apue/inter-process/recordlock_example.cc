#include <fcntl.h>
#include <unistd.h>

#include <cstring>

#include <iostream>

using namespace std;

#

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
  struct flock lock;
  lock.l_type = type;
  lock.l_start = offset;
  lock.l_whence = whence;
  lock.l_len = len;

  return fcntl(fd, cmd, &lock);
}

int main(int argc, char *argv[])
{
  const char *task_no = argv[1];
  int period = std::stoi(argv[2]);
  int counter = 0;
  int ret = 0;
  int fd = open("/tmp/filelock", O_RDWR, )

  while (true)
  {
    printf("before lock\n");
    if ((ret = lock_re(rwlock)) != 0)
    {
      perror("pthread_rwlock_wrlock error: ");
      if (ret == EOWNERDEAD)
      {
        perror("EOWNERDEAD: ");
      }
      else
      {
        perror("UNKNOWN: ");
      }
    }
    printf("task_no: %s, counter: %d\n", task_no, counter++);
    sleep(period);
    printf("before unlock\n");
    if ((ret = pthread_rwlock_unlock(rwlock)) != 0)
    {
      printf("pthread_rwlock_unlock failed\n");
      perror("error: ");
      return -1;
    }
    sleep(2);
  }

  return 0;
}
