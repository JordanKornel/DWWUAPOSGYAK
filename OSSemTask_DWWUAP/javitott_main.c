#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N 100

int szamito(char* szoveg, double kimenet[]);
void vegeredmeny_kiiro(int visszaad, double kimenet[]);
void kiiras_txt_be(int visszaad, double kimenet[], char * szoveg);

int main()
{
    key_t kulcs;
	int id;
	char *szoveg;
	kulcs=ftok(".", 'S');
    if((id=shmget(kulcs, N, IPC_CREAT|IPC_EXCL|0666))==-1)
	{
		printf("Az osztott memoria mar letezik....\n");

		if ((id=shmget(kulcs, N, 0))==-1)
		{
			perror("shmget hiba");
			exit(1);
		}
	}
	else{
		printf("Uj osztott memoria letrehozasa....\n");
	}

	if((szoveg = shmat(id, 0, 0))==(void *)-1)
	{
		perror("shmat hiba");
		exit(1);
	}
    int szamitasok_szama;
    int eredmeny;
    FILE *fp;
    double kimenet[2];
    fp= fopen("Kimenet.txt","w");
    fp= fopen("Bemenet.txt", "r");
    if (fp < 0) {
     perror("Nem sikerult a megnyitas!\n");
     exit(-1);
    }
    char* buffer;
    size_t len=N;
    fscanf(fp, "%d", &szamitasok_szama); //Jelenleg az elso sorban allunk es igy be tudjuk olvasni az i adatot!
    printf("%d db szamitast kell elvegezni.\n", szamitasok_szama);
    printf("Jelenlegi adatok:\n");
    getline(&buffer,&len,fp);
    for (int i=0; i<szamitasok_szama; i++){//Aktualis sor
        getline(&buffer,&len,fp);
        strcpy(szoveg, buffer);
        //Mindig az aktualis szamokkal dolgozunk, mert benne van az elso for ciklusban!
        eredmeny = szamito(szoveg, kimenet);
        vegeredmeny_kiiro(eredmeny, kimenet);
        kiiras_txt_be(eredmeny , kimenet, szoveg);
    }
    fclose(fp);
    shmctl(id, IPC_RMID, 0);
	printf("Memoria torolve....\n");
    return 0;
}
//Masodfokú egyenletszámító
int szamito(char* szoveg, double kimenet[]){
    int visszaad=0;
    char * token = strtok(szoveg, " "); //String split
    double bemenet[3];
    int idg=0;
     while( token != NULL ) {
      bemenet[idg]=atoi(token); // String-bõl szám
      idg++;
      token = strtok(NULL, " ");
   }
    double gyokos = sqrt((bemenet[1]*bemenet[1]) - (4*bemenet[0]*bemenet[2]));
    if (gyokos == 0){
        kimenet[0] = -(bemenet[1]/2*bemenet[0]);
        visszaad=1;
    } else if(gyokos > 0){
        kimenet[0] = -((bemenet[1]+gyokos)/(2*bemenet[0]));
        kimenet[1] = -((bemenet[1]-gyokos)/(2*bemenet[0]));
        visszaad=2;
    }
    return visszaad;
}
//Végeredményt kiírja
void vegeredmeny_kiiro(int visszaad, double kimenet[]){
    if(visszaad==2){
        printf("Ket megoldas: %.2lf, %.2lf\n", kimenet[0],kimenet[1]);
    }else if(visszaad==1) {
        printf("Egy megoldas: %.2lf\n", kimenet[0]);
    }else if(visszaad==0){
        printf("Nincs megoldas mert a gyokjel alatt nem lehet kisebb szam mint 0!\n");
    }
    return;
}
//Végeredményt beleírja e "Kimenet.txt"-be
void kiiras_txt_be(int visszaad, double kimenet[], char* szoveg){
    FILE *fp2 = fopen("Kimenet.txt", "a");
    char * token = strtok(szoveg, " ");
    double bemenet[3];
    int idg=0;
     while( token != NULL ) {
      bemenet[idg]=atoi(token);
      idg++;
      token = strtok(NULL, " ");
   }
    if (fp2 < 0) {
     perror("Nem sikerult megnyitni azt a file-t amibe kiirjuk az eredmenyeket!\n");
     exit(-1);
    }
    if(visszaad==2){
        fprintf(fp2, "a=%.2lf \t b=%.2lf \t c=%.2lf \t Elso eredmeny x=%.2lf \t Masodik eredmeny y=%.2lf\n", bemenet[0], bemenet[1], bemenet[2], kimenet[0], kimenet[1]);
    }else if(visszaad==1) {
        fprintf(fp2, "a=%.2lf \t b=%.2lf \t c=%.2lf \t Egy eredmeny x=%.2lf \n", bemenet[0], bemenet[1], bemenet[2], kimenet[0]);
    }else if(visszaad==0){
        fprintf(fp2, "a=%.2lf \t b=%.2lf \t c=%.2lf \t Nem talalhato megoldas, mert a gyokjel alatt nem lehet kisebb szam mint 0!\n", bemenet[0], bemenet[1], bemenet[2]);
    }
    fclose(fp2);
    return;
}
