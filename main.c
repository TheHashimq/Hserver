#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

int main(int argc, char *argv[]){
  int sockt = socket(AF_INET,SOCK_STREAM , 0);
  struct sockaddr_in addr = {
    AF_INET,
    0x901f,
    0,
  };
  int bindd = bind(sockt , &addr , sizeof(addr));
  listen(sockt , 10);
  int client_fd = accept(sockt , 0 ,0);
  char buffer[256] = {0};
  recv(client_fd ,buffer , 256 , 0 );
  char *f = buffer + 5;
  *strchr(f , ' ') = 0;
  int opened_fd = open(f , O_RDONLY);
  sendfile(client_fd , opened_fd , 0 , 256);
  close(opened_fd);
  close(client_fd);
  close(sockt);
  return EXIT_SUCCESS;
}
