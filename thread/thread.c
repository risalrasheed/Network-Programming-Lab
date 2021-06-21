#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int g=0;
void* function(void *var) {
  int* id=(int* )var;
  static int s=0;
  int l=0;
  ++l;
  ++s;
  ++g;
  printf("Thread id %u, PID is %u, local :%d, static :%d, global :%d\n",*id,getpid(),l,s,g);
  int a=5;
  pthread_exit((void*)a);
  sleep(5);
}

int main() {
  pthread_t tid1,tid2,tid3,tid4,tid5;
  fork();
  pthread_create(&tid1, NULL, &function, (void *)&tid1);
  pthread_create(&tid2, NULL, &function, (void *)&tid2);
  pthread_create(&tid3, NULL, &function, (void *)&tid3);
  pthread_create(&tid4, NULL, &function, (void *)&tid4);
  pthread_create(&tid5, NULL, &function, (void *)&tid5);
  int retval;
  pthread_join(tid1,(void**)&retval);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  pthread_join(tid4,NULL);
  pthread_join(tid5,NULL);
  printf("main %d\n",retval);
  return 0;
}
