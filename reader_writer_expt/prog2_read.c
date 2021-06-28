#include"prog2.h"
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define THREADSIZE 5

Values* values;

void* read(void* tid) {

  int* id=(int*) tid;

  sem_wait(&(values->read_protect));//locking (values->read_waiting)
  //critical session of (values->read_waiting)->start

  while((values->read_waiting)>(values->write_waiting));
  (values->read_waiting)++;

  sem_wait(&(values->item_protect));
  //critical session of item->start
  printf("Read of %d, item = %d\n",*id,values->item);
  //critical session of item->end
  sem_post(&(values->item_protect));

  (values->read_waiting)--;
  //critical session of (values->read_waiting)->end
  sem_post(&(values->read_protect));

  free(id);
}

void main() {
  pthread_t tid[THREADSIZE];
  key_t key = ftok("file-prog2",8);
  int shmid = shmget(key, sizeof(Values), 0666|IPC_CREAT);
  values = shmat(shmid, NULL, 0);

  for(int i=0; i<THREADSIZE; i++) {
    int *id = (int*)malloc(sizeof(int));
    *id = i;
    pthread_create(&tid[i], NULL, &read,(void*)id );
  }

  for(int i=0; i<THREADSIZE; i++) {
    pthread_join(tid[i], NULL);
  }
}
