#include "radnik.h"
KORPA korp;


void menir()
{
    char izbor;
    int provjera;
    FILE* dat;
    do
    {
        printf ("\t\t     Dobrodosli u panel za prodaju robe!\n\n\t\t\t\b\b\bUlogovani ste kao: %s\n\n",ulogovani);
        Sleep(100);
        printf ("\t\tZa izbor pritisnite broj kraj zeljene opcije!\n");
        printf ("\n\t\t 1 Dodavanje robe u korpu");
        printf ("\n\t\t 2 Pregled robe");
        printf ("\n\t\t 9 Izmjena licnih informacija");
        printf ("\n\t\t 0 ODJAVA\n");
        izbor=izbor1();
                        if (izbor=='1')
                        {
                            prodaja();
                        }
                        else if (izbor=='2')
                        {
                             system("cls");
                            zaglavljeart();
                            inorderart(root);
                            printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
                            getch();
                            system("cls");
                        }
                        else if (izbor=='9')
                        {
                        PromLicnihPod();
                        system("cls");
                        }
    }while(izbor!='0');
    upisart(dat);
    upisi(dat,root);
    SetFileAttributes("pomocna.txt",FILE_ATTRIBUTE_NORMAL);
    dat=fopen("pomocna.txt","w");
    fprintf(dat,"%s\n",imepreduzeca);
    fprintf(dat,"%d",brracuna);

    SetFileAttributes("pomocna.txt",FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_READONLY);

    fclose(dat);
}
//------------------------------------------------------------------------------
void prodaja()
{
    char c;
    char gprov;
int p;
NODE* pom;
korp.niz=(artikal*)malloc(sizeof(artikal));
korp.i=1;
korp.cijena=0;
do{
//----------------------------------------------------------------------------------------
do{
    system("cls");
        c='n';
        gprov='n';

    printf ("Unesite naziv artikla: ");
    scanf ("%s",art.naziv);
    strupr(art.naziv);
    p=trazipoimenu(art.naziv,roo);
  if (p) pom=traziposifri(art.sifra,root);
   if (p==0) {system("cls");printf ("Trazeni artikal \"%s\" trenutno ne postoji u prodavnici\nZelite li dalju kupovinu? D/N: ",art.naziv);p=0; c=getch(); system("cls");}
   else if (pom->c.kolicina==0)
   {system("cls");
       printf ("Trazeni artikal \"%s\" ne postoji trenutno na stanju.\nZelite li dalju kupovinu? D/N: ",art.naziv);p=0; c=getch(); system("cls");}
} while (c=='D' || c=='d');
if (p==1)
{
    do
    {
        system("cls");
        p=0;
    printf ("Unesite kolicinu \"%s\" po \"%s\" [ cijena %.2fKM ]: ",pom->c.naziv,pom->c.jedinica,pom->c.cijena);
    scanf ("%f",&art.kolicina);
                                if (art.kolicina <= 0)
                                {
                                    printf ("Unesena kolicina nije validna!\n");
                                    printf ("Za dalju kupovinu pritisnite 1:");
                                    p=(int)getch()-'0';
                                }
                                else if (pom->c.kolicina-art.kolicina<0)
                                {
                                printf("Nema toliko na stanju! [%.2f na stanju]",pom->c.kolicina);
                                printf("\nZa dalju kupovinu pritisnite 1: ");
                                p=(int)getch()-'0';
                                }
                                else
                                {
                                 pom->c.kolicina-=art.kolicina;
                                 korp.niz=(artikal*)realloc(korp.niz,sizeof(artikal)*(++korp.i));
                                 korp.niz[korp.i-2]=pom->c;
                                 korp.niz[korp.i-2].kolicina=art.kolicina;
                                 korp.cijena+=pom->c.cijena*art.kolicina;
                                 dizvjestaj(korp.niz[korp.i-2]);
                                 }


}while (p==1);
                            {
                            system("cls");
                            printf("NAZIV                KOLICINA MJERA CIJENA IZNOS   \n");
                            printf("==================== ======== ===== ====== ========\n");
                            for (int i=0;i<korp.i-1;i++)
                            printf("%-20s %8.2f %-5s %6.2f %6.2fKM\n",korp.niz[i].naziv,korp.niz[i].kolicina,korp.niz[i].jedinica,korp.niz[i].cijena,korp.niz[i].cijena*korp.niz[i].kolicina);
                            printf("---------------------------------------------------\n");
                            printf("UKUPNA CIJENA:                             %6.2fKM\n",korp.cijena);
                            printf("==================== ======== ===== ====== ========\n\n\n");
                            }
printf ("\nZelite li jos nesto?D/N: ");
gprov=getch();
}

//--------------------------------------------------------------------------------------------------
}while (gprov=='D' || gprov=='d');
if (korp.i!=1)
{
    if(pisiracun (&korp)==12){system("cls"); printf ("Racun izdan!\n");}
    else printf ("Greska!\n");
    Sleep(1000);
    system("cls");
}
free(korp.niz);
}


