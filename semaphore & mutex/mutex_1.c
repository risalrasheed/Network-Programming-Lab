#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

pthread_mutex_t mutex;

void* display(void* arg) {
  pthread_mutex_lock(&mutex);
  sleep(2);
  printf("display in Thread %d\n",*(int*)arg);
  pthread_mutex_unlock(&mutex);
  free(arg);
}

void main() {
  pthread_t thread_no[5];
  pthread_mutex_init(&mutex,NULL);
  for(int i=0;i<5;i++) {
    int *a =(int*) malloc(sizeof(int));
    *a=i;
    pthread_create(&thread_no[i],NULL,&display,(void*)a);

  }
  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);
}
