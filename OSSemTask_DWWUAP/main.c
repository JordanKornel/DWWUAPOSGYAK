#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int szamito(double bemenet[], double kimenet[]);
void vegeredmeny_kiiro(int visszaad, double kimenet[]);
void kiiras_txt_be(int visszaad, double kimenet[], double bemenet[]);

int main()
{
    int szamitasok_szama;
    int eredmeny;
    FILE *fp;
    double kimenet[2];
    fp= fopen("Kimenet.txt","w");
    double bemenet[3];
    fp= fopen("Bemenet.txt", "r");
    if (fp < 0) {
     perror("Nem sikerult a megnyitas!\n");
     exit(-1);
    }

    fscanf(fp, "%d", &szamitasok_szama); //Jelenleg az elso sorban allunk es igy be tudjuk olvasni az i adatot!
    printf("%d db szamitast kell elvegezni.\n", szamitasok_szama);
    printf("Jelenlegi adatok:\n");
    for (int i=0; i<szamitasok_szama; i++){//Aktualis sor
        for (int j=0; j<3; j++){//Aktualis 3 adat (oszlop)
            fscanf(fp, "%lf", &bemenet[j]);
        }
        //Mindig az aktualis szamokkal dolgozunk, mert benne van az elso for ciklusban!
        eredmeny = szamito(bemenet, kimenet);
        vegeredmeny_kiiro(eredmeny, kimenet);
        kiiras_txt_be(eredmeny , kimenet, bemenet);
    }
    fclose(fp);
    return 0;
}
//Masodfokú egyenletszámító
int szamito(double bemenet[], double kimenet[]){
    int visszaad=0;
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
void kiiras_txt_be(int visszaad, double kimenet[], double bemenet[]){
    FILE *fp2 = fopen("Kimenet.txt", "a");
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
