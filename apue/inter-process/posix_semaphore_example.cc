#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>


#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  const char *task_no = argv[1];
  int period = std::stoi(argv[2]);
  sem_t *sem = sem_open("/wdq",
                        O_CREAT,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH,
                        1);
  if (sem == SEM_FAILED)
  {
    printf("task_no: %s, sem_open failed\n", task_no);
    return -1;
  }
  int counter = 0;
  int ret = 0;

  while (true)
  {
    printf("before sem_wait\n");
    if ((ret = sem_wait(sem)) != 0)
    {
      printf("task_no: %s, sem_wait failed\n", task_no);
      return -1;
    }
    printf("task_no: %s, counter: %d\n", task_no, counter++);
    sleep(period);
    if (counter == 1)
    {
      if ((ret = sem_unlink("/wdq")) == -1)
      {
        printf("task_no: %s, sem_unlink failed\n", task_no);
        return -1;
      }
    }
    printf("before sem_post\n");
    if ((ret = sem_post(sem)) != 0)
    {
      printf("task_no: %s, sem_post failed\n", task_no);
      return -1;
    }
    sleep(2);
  }

  return 0;
}
