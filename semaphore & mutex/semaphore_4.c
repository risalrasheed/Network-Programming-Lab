#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

sem_t semaphore;

void* display(void* arg) {
  sem_wait(&semaphore);
  sleep(2);
  printf("display in Thread %d\n",*(int*)arg);
  sem_post(&semaphore);//trying withour sem_post
  free(arg);
}

void main() {
  pthread_t thread_no[5];
  sem_init(&semaphore,1,1);
  fork();
  for(int i=0;i<5;i++) {
    int *a =(int*) malloc(sizeof(int));
    *a=i;
    pthread_create(&thread_no[i],NULL,&display,(void*)a);

  }
  sem_destroy(&semaphore);
  pthread_exit(NULL);
}
