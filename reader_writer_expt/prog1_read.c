#include"prog1.h"
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define THREADSIZE 5

Values* values;
int reader_count = 0;

void* read(void* tid) {
  int* id=(int*) tid;

  pthread_mutex_lock(&(values->read_protect));//acquiring lock for reader_count
  //critical session for read ->start
  reader_count++;
  if(reader_count==1) { //first reader of a group of reader should lock item to protect from writing
    sem_wait(&(values->write_protect));
  }
  //critical session for read ->end
  pthread_mutex_unlock(&(values->read_protect));//releasing the lock of reader_count

  //any read thread can access simultanously
  printf("Read of %d, item = %d\n",*id,values->item);


  pthread_mutex_lock(&(values->read_protect));//acquiring lock for reader_count
  //critical session for read ->start
  reader_count--;
  if(reader_count==0) {//last reader of a group of reader should unlock item
    sem_post(&(values->write_protect));
  }
  //critical session for read ->end
  pthread_mutex_unlock(&(values->read_protect));//unlock read_count
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
    pthread_create(&tid[i], NULL, &read,(void*)id );
  }

  for(int i=0; i<THREADSIZE; i++) {
    pthread_join(tid[i], NULL);
  }
}
