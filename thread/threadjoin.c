#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_t tid1;
pthread_t tid2;
void* myturn(void* arg) {
  while(1) {
    printf("My Turn!\n");
    sleep(1);
  }
}
void* yourturn(void* arg) {
  while(1) {
    printf("Your Turn!\n");
    sleep(1);
    //pthread_join(tid1, NULL);
  }
}

int main() {
  //pthread_t tid;
  pthread_create(&tid1, NULL, myturn, NULL);
  pthread_create(&tid2, NULL, yourturn, NULL);

  pthread_exit(NULL);
  return 0;
}
