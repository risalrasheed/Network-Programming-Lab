#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
#include<stdio.h>
#include<stdlib.h>

void main() {
  mqd_t msgq;
  char str[10];
  struct mq_attr *attr = malloc(sizeof(struct mq_attr));
  int priority;

  msgq = mq_open("/test_q",O_RDWR);

  if(msgq == -1 ) {
    printf("Error\n");
  }
  else {

    //receiving messages
    printf("Messages\n");
    mq_getattr(msgq, attr);
    mq_receive(msgq,str,attr->mq_msgsize,&priority);
    printf("%s - %d\n",str,priority);
    mq_receive(msgq,str,attr->mq_msgsize,&priority);
    printf("%s - %d\n",str,priority);
    mq_receive(msgq,str,attr->mq_msgsize,&priority);
    printf("%s - %d\n",str,priority);
  }

}
