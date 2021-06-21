#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex;
void* function1() {
  pthread_mutex_lock(&mutex);
  //pthread_mutex_lock(&mutex); //deadlock
  sleep(5);
  printf("Function 1\n");
  printf("Function 1 Unlock %d\n",pthread_mutex_unlock(&mutex));
}
void* function2() {
  pthread_mutex_lock(&mutex); //trying with pthread_mutex_unlock
  //sleep(5);
  printf("Function 2\n");
  printf("Function 2 Unlock %d\n",pthread_mutex_unlock(&mutex));
}

void main() {
  pthread_t t1,t2;
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&t1,NULL,&function1,NULL);
  sleep(1);
  pthread_create(&t2,NULL,&function2,NULL);
  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);
}
