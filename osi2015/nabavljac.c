#include "nabavljac.h"
NODE *root=0;
artikal art;

char izbor2()
{
    fflush(stdout);
    return getch();
}


NODE* noviart (artikal *a)   // binarno stablo dodavanje prvog cvora
{
    NODE *novi1=(NODE*)malloc(sizeof(NODE));
    novi1->lijevi=novi1->desni=0;
    novi1->c=*a;
    return novi1;
}

NODE* dodajart (NODE *korijen,artikal *a) // dodavanje covra
{
    if (korijen==0) return noviart(a);
    if (strcmp(korijen->c.sifra,a->sifra)>=0)
          korijen->lijevi=dodajart(korijen->lijevi,a);
    else  korijen->desni=dodajart(korijen->desni,a);
    return korijen;
}


void zaglavljeart()///zaglavlje artikla
{
    printf("SIFRA NAZIV                KOLICINA CIJENA VRSTA");
    printf("\n===== ==================== ======== ====== ===============");
}


void inorderart(NODE* korijen)///ispis
{
    if(korijen!=0)
    {
      inorderart(korijen->lijevi);
      printf("\n%-5s %-20s %8.2f %6.2f %-15s", korijen->c.sifra, korijen->c.naziv, korijen->c.kolicina, korijen->c.cijena, korijen->c.vrsta);
      inorderart(korijen->desni);
    }
}

NODE* ucitaj_artikle (NODE *korijen) // ucitavanje iz datoteke i smijestanje u stablo
{
    FILE *dat;
    char c[1024];
    /*if (!postoji("ARTIKLI/artikli.txt"))
        {
            system("mkdir ARTIKLI"); ///kreira novi folder ako ne postoji
            dat=fopen("ARTIKLI/artikli.txt","w");
            fclose(dat);
        }*/
dat= fopen ("ARTIKLI/artikli.txt","r");
    fgets(c,1024,dat);
    fgets(c,1024,dat);
    while(fscanf(dat,"%s %s %f %f %s", art.sifra, art.naziv, &art.kolicina, &art.cijena, art.vrsta)==5)
    {
       korijen=dodajart(korijen,&art);
    }
    fclose(dat);
return korijen;
}

artikal* upis()
{
    system("cls");
    printf("SIFRA: ");scanf("%s", art.sifra);
    printf("NAZIV: ");scanf("%s", art.naziv);
    printf("KOLIC: ");scanf("%f", &art.kolicina);
    printf("CENA : ");scanf("%f", &art.cijena);
    printf("VRSTA: ");scanf("%s", art.vrsta);
    return &art;
}
void upisart(FILE *dat)
{
     dat=fopen("ARTIKLI/artikli.txt","w");
     fprintf(dat,"SIFRA NAZIV                KOLICINA CIJENA VRSTA");
     fprintf(dat,"\n===== ==================== ======== ====== ===============");
     fclose(dat);
}

void upisi(FILE *dat,NODE* korijen)
{
    dat=fopen("ARTIKLI/artikli.txt","a");
if(korijen!=0)
    {
        fprintf(dat,"\n%-5s %-20s %8.2f %6.2f %-15s", korijen->c.sifra, korijen->c.naziv, korijen->c.kolicina, korijen->c.cijena, korijen->c.vrsta);
        upisi(dat,korijen->lijevi);
        upisi(dat,korijen->desni);
    }
    fclose(dat);
}


void menin()
{
    FILE *dat;
    char izbor;
    int provjera;
    printf ("\nDobrodosli u panel za nabavu robe!\n\n");
    Sleep(100);
    printf ("Za izbor pritisnite broj kraj zeljene opcije!\n");
    do
    {
        printf ("\n\t 1 Pregled robe");
        printf ("\n\t 2 Dodaj robu");
        printf ("\n\t 3 Brisi robu");
        printf ("\n\t 4 Izmjena robe");
        printf ("\n\t 5 Izmjena licnih informacija");
        printf ("\n\t 0 ODJAVA\n");
        izbor=izbor2();
        if (izbor=='1')
        {
            system("cls");
            zaglavljeart();
            inorderart(root);
            printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
            getch();
            system("cls");
        }
        else if(izbor=='2')
        {
            root=dodajart(root,upis());
        }
        else if(izbor=='5')
        {
            PromLicnihPod();
        }
    }
    while (izbor!='0');
    upisart(dat);
    upisi(dat,root);
}
