#include<semaphore.h>
#include<pthread.h>

typedef struct Values {
  int item;
  sem_t write_protect;
  pthread_mutex_t read_protect;

}Values;
