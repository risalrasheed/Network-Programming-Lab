#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[]) {
  printf("We are in prog1.c\n");
  printf("PID of prog1.c %d\n",getpid());
  return 0;
}
