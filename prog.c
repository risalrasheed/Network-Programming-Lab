#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid=fork();
  if(pid==0) {
    sleep(10);
    printf("Child is exiting\n");

  }
  else {
    printf("Parent exiting\n");
  }
  return 0;


}
