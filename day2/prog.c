#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
void swap(int* n1, int* n2) {
  int temp=*n1;
  *n1=*n2;
  *n2=temp;
}
int partition(int* ar, int beg, int end) {
  int pivot = ar[end];
  int i=beg-1;
  for(int j=beg;j<=end;j++) {
    if(ar[j]<pivot) {
      i++;
      swap(&ar[i],&ar[j]);
    }
  }
  i++;
  swap(&ar[i],&ar[end]);
  return i;
}
void quicksort(int* ar, int beg, int end) {
  if(beg<end) {
    int index = partition(ar, beg, end);
    quicksort(ar,beg,index-1);
    quicksort(ar,index+1, end);
  }
}
int strtoint(char* str) {
  int i=0;
  int val=0;
  while(str[i]!='\0') {
    val=val*10+str[i]-'0';
    i++;
  }
  return val;
}
void main(int argc, char* argv[]) {
  int* ar=(int* )malloc(sizeof(int)*(argc-1));
  for(int i=1;i<argc;i++) {
    ar[i-1]=strtoint(argv[i]);
  }
  printf("Sorted value is ");
  quicksort(ar,0,argc-2);
  for(int i=0;i<(argc-1);i++) {
    printf("%d ",ar[i]);
  }
}

//write a program in which main program accepts integer to be sorted.
//Main program uses fork function system call, to create a new process called child,
//parent process sort the integers and wait for the child process, using the wait system call
