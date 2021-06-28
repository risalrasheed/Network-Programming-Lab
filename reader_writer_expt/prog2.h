#include<semaphore.h>
#include<pthread.h>

typedef struct Values {
  int item; //critical section variable
  sem_t read_protect; //for controlling access to critical sessions in reading
  sem_t write_protect; //for controlling access to critical sessions in writing
  sem_t item_protect; //for controlling access to item
  int write_waiting;
  int read_waiting;


}Values;
