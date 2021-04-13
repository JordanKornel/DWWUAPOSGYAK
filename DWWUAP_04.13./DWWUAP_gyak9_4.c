#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

void Terminalodas(int sig);

int main(void)
{
    if (signal(SIGTERM, Terminalodas) == SIG_ERR)
    {
        printf("Nem sikerult handlert allitani!\n");
        return 0;
    }

    while(1)
    {
        printf("Varakozas...\n");
        sleep(3);
    }

    return 0;
}

void Terminalodas(int sig)
{
    signal(sig, SIG_IGN);
    printf("SIGTERM-nek a jele: %d\n", sig);
}
