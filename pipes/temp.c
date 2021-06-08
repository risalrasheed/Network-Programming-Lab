
#include<stdio.h>
#include<string.h>
int toInt(char* operand) {
  int val=0;
  int temp=0;
  int len=strlen(operand);
  for(int i=0;i<len;i++) {
    val*=10;
    val+=(operand[i]-'0');
  }
  return val;
}
void main() {
  printf("%d",toInt("103"));
}
