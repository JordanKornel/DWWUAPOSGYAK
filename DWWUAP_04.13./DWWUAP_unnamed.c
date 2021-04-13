#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MERET 128
int main(){
char inBuffer[MERET];
int pid, fileDesc;
char input[] = "Jordán Kornél";
char * fifo = "/tmp/DWWUAP";
mkfifo(fifo, 0666);
pid = fork();
if (pid < 0)
    exit(2);
//Child
if (pid == 0){
    printf("Child: beleír pipe-ba!\n");
    fileDesc = open(fifo, O_WRONLY);
    write(fileDesc, input, strlen(input)+1);
    printf("Child: irtam a pipe-ba!\n");
}
//Parent
else if (pid > 0 ){
    fileDesc = open(fifo, O_RDONLY);
    read(fileDesc, inBuffer, strlen(input)+1);
    printf("Parent: %s\n", inBuffer);
    close(fileDesc);
}

return 0;
}
