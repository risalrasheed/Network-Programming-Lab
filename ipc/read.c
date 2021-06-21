
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{

    key_t key = ftok("shmfile",65); // creates a unique key

    int shmid = shmget(key,1024,0666|IPC_CREAT); //gives identifier associated with key

    char *str = (char*) shmat(shmid,NULL,0); //attaching str to the segment

    printf("Data read from memory: %s\n",str);

    shmdt(str); //detaching str from segment

    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL); //destroying the created segment

    return 0;
}
