#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 1
#define DEBUG 0
#define BUFFER_LEN 1024 * 1000

typedef struct client
{
  int fd;
  struct sockaddr_in client_addr;
  char send_data[BUFFER_LEN];
}client_s;

int set_addr_reuse(int server_fd)
{
  int opt = 1;
  return setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}

int set_noblock(int fd)
{
  int flags = fcntl(fd, F_GETFL, 0);
  if(flags == -1)
  {
    return -1;
  }
  flags = fcntl(fd, F_SETFL, flags|O_NONBLOCK);
  if(flags == -1)
  {
    return -1;
  }
  return 0;
}

client_s * get_one_connection(int server_fd)
{
  int ret = 0;
  struct sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(client_addr));
  int addrlen = sizeof(client_addr);
  int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
  /* ret = set_noblock(client_fd); */
  /* if(ret != 0) */
  /* { */
  /*   return NULL; */
  /* } */
  client_s *pclient= (client_s *)malloc(sizeof(client_s));
  pclient->fd = client_fd;
  pclient->client_addr = client_addr;
  return pclient;
}

void http_request_module(char *buffer, char *resource_uri)
{
  int len = strlen(buffer);
  int i = 0;
  int pre_pos = 0;

  int count = 0;
  for(i = 0; i < len; ++i)
  {
    if(buffer[i] == ' ' || buffer[i] == '\n')
    {
      ++count;
      if(count == 2)
      {
#if DEBUG
        printf("i:%d,pre_pos:%d\n",i,pre_pos);
#endif
        strncpy(resource_uri,buffer+pre_pos,i-pre_pos);
        break;
      }
      pre_pos += i + 1;
    }
  }
  printf("uri:%s\n", resource_uri);
}

void http_response_module(char *uri, void * p_client, char *resource_uri, int flags)
{
  if(flags == 404)
  {
    char *p_buffer = ((client_s *)p_client)->send_data;
    strcat(p_buffer,"HTTP/1.1 404 Not Found\r\n");
    strcat(p_buffer,"Server: http_server\r\n");
    strcat(p_buffer,"Accept-Ranges: bytes\r\n");
    //strcat(p_buffer,"ETag: W\"126-1462081014000\"\r\n");
    strcat(p_buffer,"Last-Modified: Sun, 01 May 2016 05:36:54 GMT\r\n");
    strcat(p_buffer,"Content-Type: text/html\r\n");
    strcat(p_buffer,"Content-Length: 128\r\n");
    strcat(p_buffer,"Date: Sun, 01 May 2016 05:47:47 GMT\r\n");
    strcat(p_buffer,"\r\n");
    strcat(p_buffer,"<!DOCTYPE html>\r\n");
    strcat(p_buffer,"<html>\r\n");
    strcat(p_buffer,"<head>\r\n");
    strcat(p_buffer,"<meta charset=\"UTF-8\">\r\n");
    strcat(p_buffer,"<title>404 Not Found</title>\r\n");
    strcat(p_buffer,"</head>\r\n");
    strcat(p_buffer,"<body>\r\n");
    strcat(p_buffer,"404 Not Found");
    strcat(p_buffer,"</body>\r\n");
    strcat(p_buffer,"</html>\r\n");
    return;
  }

  int uri_len = strlen(resource_uri);
  char name[20];
  memset(name, 0, 20);
   
  int i = 0;
  for(; i < uri_len; ++i)
  {
    if(resource_uri[i] == '?')
    {
      strcpy(name,resource_uri+i+1+5);
      printf("name:%s\n", name);
      break;
    }
  }

  char *p_buffer = ((client_s *)p_client)->send_data;
  strcat(p_buffer,"HTTP/1.1 200 OK\r\n");
  strcat(p_buffer,"Server: Apache-Coyote/1.1\r\n");
  strcat(p_buffer,"Accept-Ranges: bytes\r\n");
  //strcat(p_buffer,"ETag: W\"126-1462081014000\"\r\n");
  strcat(p_buffer,"Last-Modified: Sun, 01 May 2016 05:36:54 GMT\r\n");
  strcat(p_buffer,"Content-Type: text/html\r\n");
  strcat(p_buffer,"Content-Length: 128\r\n");
  strcat(p_buffer,"Date: Sun, 01 May 2016 05:47:47 GMT\r\n");
  strcat(p_buffer,"\r\n");
  strcat(p_buffer,"<!DOCTYPE html>\r\n");
  strcat(p_buffer,"<html>\r\n");
  strcat(p_buffer,"<head>\r\n");
  strcat(p_buffer,"<meta charset=\"UTF-8\">\r\n");
  strcat(p_buffer,"<title>http test</title>\r\n");
  strcat(p_buffer,"</head>\r\n");
  strcat(p_buffer,"<body>\r\n");
  strcat(p_buffer,"hello ");
  strncat(p_buffer, name, strlen(name));
  strcat(p_buffer,",i'm server.\r\n");
  strcat(p_buffer,"</body>\r\n");
  strcat(p_buffer,"</html>\r\n");
}

int main()
{
  int ret = 0;
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  int backlog = 65535;
  int maxevent = 65536;
  int port = 9997;
  char host[] = "0.0.0.0";
  if(server_fd < 0)
  {
    perror("socket failed:");
    return -1;
  }
  ret = set_addr_reuse(server_fd);
  if(ret != 0)
  {
    perror("set_addr_reuse failed:");
    return -1;
  }
	
  ret = set_noblock(server_fd);
  if(ret != 0)
  {
    perror("set_addr_reuse failed:");
    return -1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_port = htons(port);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(host);

  ret = bind(server_fd,(struct sockaddr *)&server_addr, sizeof(server_addr));
  if(ret != 0)
  {
    perror("bind failed:");
    return -1;
  }

  ret = listen(server_fd,backlog);
  if(ret != 0)
  {
    perror("listen failed:");
    return -1;
  }

  int epoll_fd = epoll_create(maxevent);
  if(epoll_fd < 0)
  {
    perror("epoll_create failed:");
    return -1;
  }
  struct epoll_event event;
  memset(&event, 0, sizeof(event));
  event.events = EPOLLIN | EPOLLERR;
  event.data.fd = server_fd;
  ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD, server_fd, &event);
  if(ret != 0)
  {
    perror("epoll_ctl error:");
  }
	
  while(1)
  {
    struct epoll_event wait_events[maxevent];
    memset(wait_events, 0, sizeof(wait_events));
    int resp_count = epoll_wait(epoll_fd, wait_events, maxevent, -1);
#if DEBUG	
    printf("resp_count:%d\n",resp_count);
#endif
    int i;
    for(i = 0; i < resp_count; ++i)
    {
      if(wait_events[i].events & EPOLLIN)
      {
#if DEBUG	
        printf("----read events block----\n");
#endif
        if(wait_events[i].data.fd == server_fd)
        {
          client_s *client = get_one_connection(server_fd);
          struct epoll_event client_event;
          memset(&client_event, 0, sizeof(client_event));
          client_event.events = EPOLLIN | EPOLLERR;
          client_event.data.ptr = client;
          ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client->fd, &client_event);
          if(ret != 0)
          {
            perror("epoll_ctl error:");
          }
        }
        else
        {
          client_s *p_client = wait_events[i].data.ptr;
          char buffer[BUFFER_LEN];
          memset(buffer, 0, sizeof(buffer));
#if BLOCK
          /* sleep(10); */
#endif
          int n = 0;
          while (1) {
              n = read(p_client->fd, buffer, BUFFER_LEN);
              printf("read size %d\n", n);
          }
          if(n < -1)
          {
            perror("read failed:");
          }
          else if(n == 0)
          {
            printf("close\n");
            ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL,p_client->fd,0);
            if(ret != 0)
            {
              perror("epoll_ctl error:");
            }

            close(p_client->fd);
            free(p_client);
          }
          else
          {
            printf("recv data count: %d\n", n);
            printf("client say:%s\n",buffer);
            char uri[2048];
            memset(uri, 0, 2048);
            http_request_module(buffer,uri);
            if(!strncmp("/index.html", uri, strlen("/index.html")))
            {
              http_response_module(uri,wait_events[i].data.ptr, uri, 200);
							
            }
            else
            {
              http_response_module(uri,wait_events[i].data.ptr, uri,404);
            }
            wait_events[i].events |= EPOLLOUT;
            ret = epoll_ctl(epoll_fd, EPOLL_CTL_MOD,p_client->fd, &wait_events[i]);
            if(ret != 0)
            {
              perror("epoll_ctl error:");
            }
          }
        }
      }

      if(wait_events[i].events & EPOLLOUT)
      {
#if DEBUG	
        printf("----write events block----\n");
#endif
        client_s *p_client = wait_events[i].data.ptr;
        printf("we will write:%s\n",p_client->send_data);
#if BLOCK
        /* sleep(10); */
#endif
        int n = write(p_client->fd, p_client->send_data, strlen(p_client->send_data));
        printf("has writed :%d\n", n);
        if(n < -1)
        {
          perror("write failed");
        }
        else
        {
          memset(p_client->send_data, 0, BUFFER_LEN);
#if 0
          wait_events[i].events ^= EPOLLOUT;
          ret = epoll_ctl(epoll_fd, EPOLL_CTL_MOD, p_client->fd, &wait_events[i]);
          if(ret != 0)
          {
            perror("epoll_ctl error:");
          }
#endif
          ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL,p_client->fd,0);
          if(ret != 0)
          {
            perror("epoll_ctl error:");
          }
          close(p_client->fd);
          free(p_client);
        }
      }
			
      if(wait_events[i].events & EPOLLERR)
      {
        printf("----error events block----\n");
        perror("error:");
      }
    }
  }

  return 0;
}
