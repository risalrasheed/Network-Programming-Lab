#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

#define COUNT 5 //defines number threads of read & write to create

pthread_mutex_t read_protect; //for controlling access to critical sessions in reading
sem_t write_protect; //for preventing writing while reading and vice versa
int reader_count=0;
int item=100; //shared item

//function for writing
void* write(void* tid) {
  int* id=(int*) tid;

  sem_wait(&write_protect);//acquiring lock of the item
  //critical section ->start
  item++;
  printf("Write of %d, item = %d\n",*id,item);
  //critical section ->end

  sem_post(&write_protect);//releasing lock
  free(id);
}

//function for reading
void* read(void* tid) {
  int* id=(int*) tid;

  pthread_mutex_lock(&read_protect);//acquiring lock for reader_count
  //critical session for read ->start
  reader_count++;
  if(reader_count==1) { //first reader of a group of reader should lock item to protect from writing
    sem_wait(&write_protect);
  }
  //critical session for read ->end
  pthread_mutex_unlock(&read_protect);//releasing the lock of reader_count

  //any read thread can access simultanously
  printf("Read of %d, item = %d\n",*id,item);


  pthread_mutex_lock(&read_protect);//acquiring lock for reader_count
  //critical session for read ->start
  reader_count--;
  if(reader_count==0) {//last reader of a group of reader should unlock item
    sem_post(&write_protect);
  }
  //critical session for read ->end
  pthread_mutex_unlock(&read_protect);//unlock read_count
  free(id);
}


void main() {
  //initialising semaphore and mutex
  sem_init(&write_protect,0,1);
  pthread_mutex_init(&read_protect,NULL);


  pthread_t thread_no_read[COUNT]; //to store ids of read threads
  pthread_t thread_no_write[COUNT]; //to store ids of write threads

  //creating read & write threads
  for(int i=0;i<COUNT;i++) {
    int *r =(int*) malloc(sizeof(int));
    *r=i;
    int *w =(int*) malloc(sizeof(int));
    *w=i;
    pthread_create(&thread_no_read[i],NULL,&read,(void*)r);
    pthread_create(&thread_no_write[i],NULL,&write,(void*)w);
  }
  //making parent thread wait before semaphore & mutex is destroyed
  for(int i=0;i<COUNT;i++) {
    pthread_join(thread_no_read[i],NULL);
    pthread_join(thread_no_write[i],NULL);
  }
  //destroy semaphore&mutex
  pthread_mutex_destroy(&read_protect);
  sem_destroy(&write_protect);
  pthread_exit(NULL);
}
