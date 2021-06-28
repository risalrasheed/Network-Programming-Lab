#include"prog2.h"
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<pthread.h>
#include<errno.h>



void main() {
  int a;
  key_t key = ftok("file-prog2",8);
  int shmid = shmget(key, sizeof(Values), 0666|IPC_CREAT);
  Values* values = (Values*)shmat(shmid,NULL,0);

  values->item = 100;

  values->read_waiting = 0;
  values->write_waiting = 0;

  sem_init(&(values->write_protect),1,1);
  sem_init(&(values->read_protect),1,1);
  sem_init(&(values->item_protect),1,1);

  shmdt(values);

}
