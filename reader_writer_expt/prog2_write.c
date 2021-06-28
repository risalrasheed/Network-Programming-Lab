#include"prog2.h"
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

  //lock write)waiting from other writers
  sem_wait(&(values->write_protect));
  //critical session of (values->write_waiting)->start
  //while((values->write_waiting)>(values->read_waiting)); //if more read threads are waiting then wait
  (values->write_waiting)++;

  //locking item
  sem_wait(&(values->item_protect));
  //critical session of item->start
  (values->item)++;
  printf("Write of %d, item = %d\n",*id,values->item);
  //critical session of item->start
  sem_post(&(values->item_protect));//unclocking item

  (values->write_waiting)--; //removing current write thread from wait
  //critical session of (values->write_waiting)->end
  sem_post(&(values->write_protect)); //release (values->write_waiting)
  //printf("hello\n");
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
    pthread_create(&tid[i], NULL, &write,(void*)id );
  }

  for(int i=0; i<THREADSIZE; i++) {
    pthread_join(tid[i], NULL);
  }
}
