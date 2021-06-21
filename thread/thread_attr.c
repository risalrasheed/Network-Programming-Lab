
#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
struct para {
  int a;
  int b;
};
void* threadFunction(void* obj_addr_temp) {
  struct para* obj_addr=(struct para*)obj_addr_temp;
  printf("Parameter value %d %d\n",obj_addr->a,obj_addr->b);
  printf("Thread function is running\n");
  sleep(5);
  printf("Thread function is exiting\n");
}

void main() {
  struct para obj;
  obj.a=1;
  obj.b=2;
  pthread_t t1;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  printf("Main function begins\n");
  pthread_create(&t1,&attr,&threadFunction,(void*)&obj);
  pthread_join(t1,NULL);
  printf("Main function ends\n");
}
