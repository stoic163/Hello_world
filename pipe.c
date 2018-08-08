#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[])
{
  int pipe_fd[2];
  pid_t child_pid;
  char pipe_buf;
  memset(pipe_fd, 0, sizeof(int)*2);
  
  if (pipe(pipe_fd) == -1) {
    return -1;
  }
  
  if (child_pid == 0) {
    close(pipe_fd[1]);
    while(read(pipe_fd[0], &pipe_buf, 1) > 0)
      write(STDOUT_FILENO, &pipe_buf, 1);
    close(pipe_fd[0]);
    return 0;
  } else {
    close(pipe_fd[0]);
    write(pipe_fd[1], "H", 1);
    close(pipe_fd[1]);
    wait(NULL);
    return 0;
  }
}
