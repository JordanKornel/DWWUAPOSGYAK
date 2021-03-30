#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

void Megszakito(int jel);
void Kilepes(int jel);

int Megszakitas = 0;

int main(void)
{
    if (signal(SIGINT, Megszakito) == SIG_ERR)
    {
        printf("A kezelo nem mukodik!(SIGINT)\n");
        return 0;
    }

    if (signal(SIGQUIT, Kilepes) == SIG_ERR)
    {
        printf("A kezelo nem mukodik!(SIGINT)\n");
        return 0;
    }
    printf("A megszakitas jelenleg: %d", Megszakitas);
    while(Megszakitas < 2)
	printf("Kell egy masodik jel is:\n");
        sleep(1);
    printf("2. (SIGINT) jel!");
    return 0;
}

void Megszakito(int jel)
{
    printf("SIGINT jel: %d\n", jel);
    Megszakitas++;
}

void Kilepes(int sig)
{
    printf("SIGQUIT jel: %d\n", jel);
}