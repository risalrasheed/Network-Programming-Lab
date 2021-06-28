#include"prog1.h"
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define THREADSIZE 5

Values* values;

void* write(void* tid) {
  int* id=(int*) tid;

  sem_wait(&(values->write_protect));//acquiring lock of the item
  //critical section ->start
  values->item += 1;
  printf("Write of %d, item = %d\n",*id,values->item);
  //critical section ->end

  sem_post(&(values->write_protect));//releasing lock
  free(id);
}

void main() {
  pthread_t tid[THREADSIZE];
  key_t key = ftok("file",7);
  int shmid = shmget(key, sizeof(Values), 0666|IPC_CREAT);
  values = shmat(shmid, NULL, 0);

  for(int i=0; i<THREADSIZE; i++) {
    int *id = (int*)malloc(sizeof(int));
    *id = i;
    pthread_create(&tid[i], NULL, &write,(void*)id );
  }

  for(int i=0; i<THREADSIZE; i++) {
    pthread_join(tid[i], NULL);
  }
}
