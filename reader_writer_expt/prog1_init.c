#include"prog1.h"
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<pthread.h>



void main() {

  key_t key = ftok("file",7);
  int shmid = shmget(key, sizeof(Values), 0666|IPC_CREAT);
  Values* values = (Values*)shmat(shmid,NULL,0);

  values->item = 100;
  sem_init(&(values->write_protect),1,1);
  pthread_mutex_init(&(values->read_protect), NULL);

  shmdt(values);

}
