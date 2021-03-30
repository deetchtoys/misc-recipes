#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define DATA_LEN (1024 * 1000)


int main()
{
  char data[DATA_LEN];
  FILE* fp = fopen("/home/seventh/audio/575d9c1e-7122-4eba-9295-7975f163a4bd-0.wav", "rb");
  int n = fread(data, sizeof(unsigned char), DATA_LEN, fp);
  printf("read size %d\n", n);
  int ret = 0;
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0)
  {
    perror("socket failed:");
    return -1;
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(9997);
  servaddr.sin_addr.s_addr = inet_addr("172.16.20.23");
  ret = connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  if(ret != 0)
  {
    perror("connect failed:");
    return -1;
  }
  time_t now;
  time(&now);
  int m = write(fd, data, n);
  if(n < 0)
  {
    perror("write failed:");
    return -1;
  }

  time_t now1;
  time(&now1);
  printf("write %d cost %d\n", m, now1-now);
  memset(data, 0, strlen(data));
  n = read(fd,data,DATA_LEN);
  if(n < 0)
  {
    perror("read failed:");
  }
  else if(n == 0)
  {
    printf("close client\n");
    close(fd);
  }
  else
  {
    printf("server say:%s\n", data);
  }

  return 0;
}
