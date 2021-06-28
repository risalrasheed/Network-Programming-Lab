#include "prog1.h"
#include<sys/shm.h>
#include<sys/ipc.h>
#include<semaphore.h>
#include<pthread.h>
Values* values;
void main() {
  key_t key = ftok("file",7);
  int shmid = shmget(key, sizeof(Values), IPC_CREAT|0666);
  values = (Values*)shmat(shmid, NULL, 0);

  sem_destroy(&(values->write_protect));
  pthread_mutex_destroy(&(values->read_protect));
  shmdt(values);
  shmctl(shmid,IPC_RMID,NULL);
}
