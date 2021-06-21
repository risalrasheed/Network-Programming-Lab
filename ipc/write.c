
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<string.h>

int main()
{

    key_t key = ftok("shmfile",65);// creates a unique key

    int shmid = shmget(key,1024,0666|IPC_CREAT); //gives identifier associated with key

    char *str = (char*) shmat(shmid,NULL,0); //attaching str to the segment

    printf("Write Data : ");
    fgets(str,50,stdin);

    printf("Data written in memory: %s\n",str);
    printf("Write Data : ");
    str=str+strlen(str);
    fgets(str,50,stdin);

    printf("Data written in memory: %s\n",str);

    shmdt(str); //detaching

    return 0;
}
