#ifndef SHARED_MEMORY_MANAGER_H_
#define SHARED_MEMORY_MANAGER_H_

#include <sys/shm.h>
#include <sys/ipc.h>

#include <string>

using std::string;

class SharedMemoryManager
{
  key_t key_;
  string path_;
  int proj_id_;
  int shm_id_;
  int shm_size_;
  int shm_flag_;

 public:
  SharedMemoryManager(const string &path, int proj_id, int shm_size, int shm_flag)
      : path_(path)
      , proj_id_(proj_id)
      , shm_size_(shm_size)
      , shm_flag_(shm_flag)
  {}

  int Init()
  {
    key_ = ftok(path_.c_str(), proj_id_);
    if (key_ == -1)
    {
      return -1;
    }

    shm_id_ = shmget(key_, shm_size_, shm_flag_);
    if (shm_id_ == -1)
    {
      return -1;
    }

    return 0;
  }

  int Shmctl(int cmd, shmid_ds &buf)
  {
    int result = shmctl(shm_id_, cmd, &buf);
    if (result == -1)
    {
      return -1;
    }


    return 0;
  }

  //映射地址
  void * Shmat(const void *addr, int flag)
  {
    return shmat(shm_id_, addr, flag);
  }

  //分离
  int Shmdt(const void *addr)
  {
    return shmdt(addr);
  }
};


#endif
