#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

sem_t semaphore;
void* function1() {
  int a;
  sem_post(&semaphore);
  sem_getvalue(&semaphore,&a);
  printf("Semaphore value-%d\n",a);
  sem_wait(&semaphore);
  sleep(5);
  printf("Function 1\n");
  sem_post(&semaphore);
}
void* function2() {
  sem_wait(&semaphore);
  //sleep(5);
  printf("Function 2\n");
  sem_post(&semaphore);
}

void main() {
  pthread_t t1,t2;
  sem_init(&semaphore,0,1); //trying a different semaphore value paramater
  pthread_create(&t1,NULL,&function1,NULL);
  pthread_create(&t2,NULL,&function2,NULL);
  sem_destroy(&semaphore);
  pthread_exit(NULL);
}
