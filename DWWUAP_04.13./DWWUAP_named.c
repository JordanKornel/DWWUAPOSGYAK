#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MERET 10
int main(){
char inBuffer[MERET];
int p[2], nbytes, pid;
if (pipe(p) < 0){
    perror("Pipe hiba");
    exit(1);
}
pid = fork();
if (pid < 0)
    exit(2);
//Child
if (pid == 0){
    printf("Child: Iras \n");
    write(p[1], "JK DWWUAP", MERET);
    printf("Child: Beleiras\n");
}
//Parent
else if (pid > 0 ){
    wait(NULL);
    read(p[0], inBuffer, MERET);
    printf("Parent: Kiolvasas: %s\n", inBuffer);
}

return 0;
}
