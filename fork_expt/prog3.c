#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int a;
  int parent=-1;
  int status;
  printf("%d - Parent\n",getpid());
  if(fork()==0) {

    printf("%d - Child1 Created\n",getpid());

    if(fork()==0) {

      printf("%d - Child2 created\n",getpid());
      if(fork()==0) {
        printf("%d - Child3 Created\n",getpid());
        exit(1);
      }
      else {
        wait(&status);
        printf("%d status to child2\n",WEXITSTATUS(status));
      }
    }
    else {
      wait(&status);
      printf("%d status to child1\n",WEXITSTATUS(status));
    }
  }
  else {
    wait(&status);
    printf("%d status to parent\n",WEXITSTATUS(status));
  }

  printf("Terminating PID is %d\n",getpid());


}
