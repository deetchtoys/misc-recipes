#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <pthread.h>

#include <cstring>

#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
  const char *task_no = argv[1];
  int period = std::stoi(argv[2]);
  int counter = 0;
  int ret = 0;

  key_t key = 0;
  if ((key = ftok("/tmp/wdq", 100)) == -1)
  {
    printf("ftok failed\n");
    perror("error: ");
    return -1;
  }

  int shm_id = 0;
  if ((shm_id = shmget(key, sizeof(pthread_rwlock_t), IPC_CREAT)) == -1)
  {
    printf("shmget failed\n");
    perror("error: ");
    return -1;
  }

  void *shm_addr = 0;
  if ((shm_addr = shmat(shm_id, 0, 0)) == (void *)-1)
  {
    printf("shmat failed\n");
    perror("error: ");
    return -1;
  }

  pthread_rwlock_t *rwlock = (pthread_rwlock_t *)shm_addr;
  pthread_rwlockattr_t rwlockattr;
  if (strcmp(task_no, "1") == 0)
  {
    if ((ret = pthread_rwlockattr_init(&rwlockattr)) != 0)
    {
      printf("pthread_rwlockattr_init failed\n");
      perror("error: ");
      return -1;
    }

    if ((ret = pthread_rwlockattr_setpshared(&rwlockattr, PTHREAD_PROCESS_SHARED)) != 0)
    {
      printf("pthread_rwlockattr_setpshared failed\n");
      perror("error: ");
      return -1;
    }

    if ((ret = pthread_rwlock_init(rwlock, &rwlockattr)) != 0)
    {
      printf("pthread_rwlock_init failed\n");
      perror("error: ");
      return -1;
    }
  }

  while (true)
  {
    printf("before lock\n");
    if ((ret = pthread_rwlock_wrlock(rwlock)) != 0)
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
