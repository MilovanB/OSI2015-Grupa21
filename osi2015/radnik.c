#include "radnik.h"

void menir()
{
    char izbor;
    int provjera;
    printf ("\t\t     Dobrodosli u panel za prodaju robe!\n\n");
    Sleep(100);
    printf ("\t\tZa izbor pritisnite broj kraj zeljene opcije!\n");
    do
    {
        printf ("\n\t\t 1 Dodavanje robe u korpu");
        printf ("\n\t\t 2 Pregled robe");
        printf ("\n\t\t 9 Izmjena licnih informacija");
        printf ("\n\t\t 0 ODJAVA\n");
        izbor=izbor2();
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
}

void prodaja()
{
    char c;
FILE *dat;
int p;

do{
    system("cls");
        c='D';
    printf ("Unesite naziv artikla: ");
    scanf ("%s",art.naziv);
    printf ("\n%s\n",art.naziv);
    p=trazipoimenu(art.naziv,root);
    printf ("%d\n\n",p);
   if (p==1) {printf ("Trazeni artikal '%s' ne postoji trenutno na stanju.\nZelite li dalju prodaju? D/N: ",art.naziv); c=getch(); system("cls");}
   else if (p==0) {printf ("Trazeni artikal '%s' trenutno ne postoji u prodavnici\nZelite li dalju prodaju? D/N: ",art.naziv);
    c=getch();
    system("cls");}
} while (c=='D' || c=='d');
}


int trazipoimenu(char* naziv,NODE* korijen)
{
    if (korijen==0) return 0;
    printf ("\n%s\n",korijen->c.naziv);
    if (strcmp(naziv,korijen->c.naziv)==0)
    {
        if (korijen->c.kolicina==0) return 1;
        else return 2;
        }
    else if (strcmp(naziv,korijen->c.naziv)<0)  return trazipoimenu (naziv,korijen->lijevi);
    else return  trazipoimenu (naziv,korijen->desni);
}
