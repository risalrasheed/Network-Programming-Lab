#include <stdio.h>
#include<pthread.h>
#include<unistd.h>

void* threadFunction() {
  printf("Thread function is running\n");
  sleep(5);
  printf("Thread function is exiting\n");
}

void main() {
  pthread_t t1;
  printf("Main function begins\n");
  pthread_create(&t1,NULL,&threadFunction,NULL);
  pthread_join(t1,NULL);
  printf("Main function ends\n");
}
