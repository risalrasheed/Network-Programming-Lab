#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
#include<stdio.h>
#include<string.h>

void main() {
  char msg1[]="Message 1";
  char msg2[]="Message 2";
  char msg3[]="Message 3";
  mqd_t msgq;
  msgq = mq_open("/test_q",O_CREAT|O_RDWR,0666,NULL);
  if(msgq==-1) {
    printf("Error creating queue\n");

  }
  else {
    //sending messages with priority
    mq_send(msgq,msg1,strlen(msg1),3);
    mq_send(msgq,msg2,strlen(msg2),1);
    mq_send(msgq,msg3,strlen(msg3),2);
    printf("Successfully send\n");
  }


}
