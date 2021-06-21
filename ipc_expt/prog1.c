#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>
#include<string.h>

//counting number of charachters(alphabets and numbers) in string
int getNumChar(char* read_message) {
  int char_num=0;
  for(int i=0;read_message[i]!='\0';i++) {
    if(isalnum(read_message[i])!=0) {
      char_num++;

    }
  }
  return char_num;
}

//counting number of words
int getNumWord(char* read_message) {
  int word_num=0;
  for(int i=0;read_message[i]!='\0';i++) {
    while(isalnum(read_message[i])==0) {
      i++;
    }
    if(isalnum(read_message[i])!=0) {
      word_num++;
    }
    while(isalnum(read_message[i])!=0) {
      i++;
    }
  }
  return word_num;
}

//counting number of lines
int getNumLine(char* read_message) {
  int line_num=0;
  for(int i=0;read_message[i]!='\0';i++) {
    if(read_message[i]=='.'||read_message[i]=='!'||read_message[i]=='\n') {
      line_num++;
    }
  }
  return line_num;
}
//
void main() {
  int pipefds_1[2], pipefds_2[2];
  int return_status_1, return_status_2;
  //char write_message[]={"hello world\n The sun is shining bright\n It is a good day for a walk\n"};
  char write_message[100];
  char read_message[100];

  printf("Enter the string ");
  scanf("%[^~]",write_message);
  //creating two pipes
  return_status_1 = pipe(pipefds_1);
  return_status_2 = pipe(pipefds_2);
  if(return_status_1 == -1||return_status_2 == -1) {
    printf("Error cannot create pipe\n");
  }
  else {


      if(fork()==0) {
        int word_num,char_num,line_num;
        //child reading message from pipe 1
        read(pipefds_1[0],read_message, sizeof(read_message));
        char_num=getNumChar(read_message);
        word_num=getNumWord(read_message);
        line_num=getNumLine(read_message);

        char temp_str[3];
        //child writing details to pipe 2
        sprintf(temp_str,"%d",char_num);
        write(pipefds_2[1],temp_str,sizeof(temp_str));
        sprintf(temp_str,"%d",word_num);
        write(pipefds_2[1],temp_str,sizeof(temp_str));
        sprintf(temp_str,"%d",line_num);
        write(pipefds_2[1],temp_str,sizeof(temp_str));

      }
      else {
        //parent writing string to pipe 1
        write(pipefds_1[1], write_message, sizeof(write_message));
        printf("Message written\n");
        wait(NULL);
        char temp_str[3];
        //parent reading details from pipe 2
        read(pipefds_2[0],temp_str,sizeof(temp_str));
        printf("Number of characters %s\n",temp_str);
        read(pipefds_2[0],temp_str,sizeof(temp_str));
        printf("Number of words %s\n",temp_str);
        read(pipefds_2[0],temp_str,sizeof(temp_str));
        printf("Number of lines %s\n",temp_str);
      }
  }

}
