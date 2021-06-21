#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

#define COUNT 5 //defines number threads of read & write to create

sem_t read_protect; //for controlling access to critical sessions in reading
sem_t write_protect; //for controlling access to critical sessions in writing
sem_t item_protect; //for controlling access to item

int item=100; //shared item
int write_waiting=0; //count of currently waiting write thread
int read_waiting=0; //count of currently waiting read thread

void* writer(void* tid) {
  int* id=(int*) tid;

  //lock write)waiting from other writers
  sem_wait(&write_protect);
  //critical session of write_waiting->start
  while(write_waiting>read_waiting); //if more read threads are waiting then wait
  write_waiting++;

  //locking item
  sem_wait(&item_protect);
  //critical session of item->start
  item++;
  printf("Write of %d, item = %d\n",*id,item);
  //critical session of item->start
  sem_post(&item_protect);//unclocking item

  write_waiting--; //removing current write thread from wait
  //critical session of write_waiting->end
  sem_post(&write_protect); //release write_waiting
  //printf("hello\n");
  free(id);
}

void* reader(void* tid) {

  int* id=(int*) tid;

  sem_wait(&read_protect);//locking read_waiting
  //critical session of read_waiting->start

  while(read_waiting>write_waiting);
  read_waiting++;

  sem_wait(&item_protect);
  //critical session of item->start
  printf("Read of %d, item = %d\n",*id,item);
  //critical session of item->end
  sem_post(&item_protect);

  read_waiting--;
  //critical session of read_waiting->end
  sem_post(&read_protect);

  free(id);
}


void main() {
  //initialising all semaphores
  sem_init(&write_protect,0,1);
  sem_init(&read_protect,0,1);
  sem_init(&item_protect,0,1);


  pthread_t thread_no_read[COUNT]; //to store ids of read threads
  pthread_t thread_no_write[COUNT]; //to store ids of write threads

  //creating read & write threads
  for(int i=0;i<COUNT;i++) {
    int *r =(int*) malloc(sizeof(int));
    *r=i;
    int *w =(int*) malloc(sizeof(int));
    *w=i;
    pthread_create(&thread_no_read[i],NULL,&reader,(void*)r);
    pthread_create(&thread_no_write[i],NULL,&writer,(void*)w);
  }

  //making parent thread wait before semaphore & mutex is destroyed
  for(int i=0;i<COUNT;i++) {
    pthread_join(thread_no_read[i],NULL);
    pthread_join(thread_no_write[i],NULL);
  }

  //destroy semaphore
  sem_destroy(&read_protect);
  sem_destroy(&write_protect);
  pthread_exit(NULL);
}
