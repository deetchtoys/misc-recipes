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
  if ((shm_id = shmget(key, sizeof(pthread_mutex_t), IPC_CREAT)) == -1)
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

  pthread_mutex_t *mutex = (pthread_mutex_t *)shm_addr;
  pthread_mutexattr_t mutexattr;
  if (strcmp(task_no, "1") == 0)
  {
    if ((ret = pthread_mutexattr_init(&mutexattr)) != 0)
    {
      printf("pthread_mutexattr_init failed\n");
      perror("error: ");
      return -1;
    }

    if ((ret = pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED)) != 0)
    {
      printf("pthread_mutexattr_setpshared failed\n");
      perror("error: ");
      return -1;
    }

    if ((ret = pthread_mutexattr_setrobust(&mutexattr, PTHREAD_MUTEX_ROBUST)) != 0)
    {
      printf("pthread_mutexattr_setpshared failed\n");
      perror("error: ");
      return -1;
    }

    if ((ret = pthread_mutex_init(mutex, &mutexattr)) != 0)
    {
      printf("pthread_mutex_init failed\n");
      perror("error: ");
      return -1;
    }
  }

  while (true)
  {
    printf("before lock\n");
    if ((ret = pthread_mutex_lock(mutex)) != 0)
    {
      perror("pthread_mutex_lock error: ");
      if (ret == EOWNERDEAD)
      {
        if ((ret = pthread_mutex_consistent(mutex)) != 0)
        {
          printf("pthread_mutex_consistent handler\n");
        }
        else
        {
          printf("recovered\n");
        }
      }
      else
      {
        printf("can't recover\n");
        return -1;
      }
    }
    printf("task_no: %s, counter: %d\n", task_no, counter++);
    sleep(period);
    printf("before unlock\n");
    if ((ret = pthread_mutex_unlock(mutex)) != 0)
    {
      printf("pthread_mutex_unlock failed\n");
      perror("error: ");
      return -1;
    }
    sleep(2);
  }

  return 0;
}
