#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>
#include<string.h>
void get_string(char* str) {

  fgets(str,100,stdin);
  if(strcmp(str,"\n")==0) {
    fgets(str,100,stdin);
  }
  int str_len=strlen(str);
  if(str[str_len-1]=='\n') {
    str[str_len-1]='\0';
  }
}
//function to concatinate string
void concatinate(char* msg1, char* msg2) {
  int i=0;
  for( ; msg1[i]!='\0'; i++);
  int j=0;
  for( ; msg2[j]!='\0'; j++) {
    msg1[i+j]=msg2[j];

  }
  msg1[i+j]='\0';
}

void main() {
  int pipefds_1[2], pipefds_2[2];
  int return_status_1, return_status_2;
  char write_message[100];
  char read_message[200];
  return_status_1 = pipe(pipefds_1);
  return_status_2 = pipe(pipefds_2);
  if(return_status_1 == -1||return_status_2 == -1) {
    printf("Error cannot create pipe\n");
  }
  else {
      if(fork()==0) {//child
        //reading from pipe1
        read(pipefds_1[0],read_message, sizeof(read_message));
        printf("Enter the string to concatinate ");
        get_string(write_message);
        concatinate(read_message,write_message);

        //writing to pipe 2
        write(pipefds_2[1],read_message,sizeof(read_message));
        printf("written to pipe 2\n");
      }
      else {//parent
        //writing to pipe 1
        printf("Enter first string ");
        get_string(write_message);
        write(pipefds_1[1], write_message, sizeof(write_message));
        printf("Message written to pipe 1\n");
        wait(NULL);

        //reading from pipe 2
        read(pipefds_2[0],read_message,sizeof(read_message));
        printf("concatinated string - %s\n",read_message);
      }
  }

}
