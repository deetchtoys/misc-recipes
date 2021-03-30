#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>


#include <iostream>

using namespace std;

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int main(int argc, char *argv[])
{
  const char *task_no = argv[1];
  int period = std::stoi(argv[2]);
  key_t key = 0;
  if ((key = ftok("/tmp/wdq", 101)) == -1)
  {
    printf("ftok failed\n");
    perror("error: ");
    return -1;
  }

  int sem_id = 0;
  if ((sem_id = semget(key, 1, 0664 | IPC_CREAT)) == -1)
  {
    printf("semget failed\n");
    perror("error: ");
    return -1;
  }

  int counter = 0;
  int ret = 0;
  struct sembuf semoparray[1];
  union semun u;
  u.val = 1;
  // if (semctl(sem_id, 0, SETVAL, u) < 0) { // SETVAL is a macro to specify that you're setting the value of the semaphore to that specified by the union u
  //   /* error handling code */
  //   printf("semctl failed\n");
  //   perror("error: ");
  //   return -1;
  // }
  while (true)
  {
    printf("before sem_wait\n");
    semoparray[0].sem_num = 0;
    semoparray[0].sem_op = -1;
    semoparray[0].sem_flg = SEM_UNDO;
    if ((ret = semop(sem_id, semoparray, 1)) != 0)
    {
      printf("task_no: %s, accquire semop failed\n", task_no);
      perror("error: ");
      return -1;
    }
    printf("task_no: %s, counter: %d\n", task_no, counter++);
    sleep(period);

    printf("before sem_post\n");
    semoparray[0].sem_num = 0;
    semoparray[0].sem_op = 1;
    semoparray[0].sem_flg = SEM_UNDO;
    if ((ret = semop(sem_id, semoparray, 1)) != 0)
    {
      printf("task_no: %s, release semop failed\n", task_no);
      perror("error: ");
      return -1;
    }
    sleep(2);
  }

  return 0;
}
