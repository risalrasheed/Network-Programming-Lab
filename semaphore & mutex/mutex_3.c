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
  printf("Function 1 unlock1 %d\n",pthread_mutex_unlock(&mutex)!=0);
}
void* function2() {
  printf("Function 2 unlock1 %d\n",pthread_mutex_unlock(&mutex)!=0);//trying with pthread_mutex_unlock
  //sleep(5);
  printf("Function 2\n");
  printf("Function 2 unlock2 %d\n",pthread_mutex_unlock(&mutex)!=0);
}

void main() {
  pthread_t t1,t2;
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ERRORCHECK);
  pthread_mutex_init(&mutex,&attr);
  pthread_create(&t1,NULL,&function1,NULL);
  sleep(1);
  pthread_create(&t2,NULL,&function2,NULL);
  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);
}
