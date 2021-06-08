#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<string.h>
int strtoint(char* str) {
  int len=strlen(str);
  int val=0;
  for(int i=0;i<len;i++) {
    val=(val*10)+(str[i]-'0');
  }
  return val;
}
int main(int argc, char *argv[]) {
  int n = strtoint(argv[1]);
  int fact=1;
  if(fork()==0) {
    for(int i=1;i<=n;i++) {
      fact*=i;
      printf("%d ",fact);
    }

  }
 return 0;
}
