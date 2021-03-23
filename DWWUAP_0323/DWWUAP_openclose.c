#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NEPTUN "DWWUAP.txt"

int main()
{
    int filename = open(NEPTUN, O_RDWR);
    if(filename == -1)
    {
        printf("Nem sikerult megnyitni a fajlt!\n");
        return 1;
    } else printf("Sikerult megnyitni!");

    char tartalom[64];
    int olvasott = read(filename, tartalom, sizeof(tartalom));

    tartalom[olvasott] = '\0';
    printf("beolvasott adatok: \"%s\" osszesen \"%i\" byte.\n", tartalom, olvasott);

    lseek(filename, 0, SEEK_SET);

    char szoveg[] = "File-ba iras";
    int irt = write(filename, szoveg, sizeof(szoveg));
    printf("A fajlba irtuk a(z) \"%s\" szoveget. osszesen \"%i\" byte.\n", szoveg, irt);
    close(filename);
    return 0;
}
