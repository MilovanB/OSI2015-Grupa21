#include "admin.h"

char izbor1()
{
  fflush(stdout);
 return getch();
}



CVOR* najmanji(CVOR* korijen)
{
    while (korijen->lijevi != NULL) korijen=korijen->lijevi;
    return korijen;
}

CVOR* brisi(CVOR *korijen, char* username)
{
    CVOR *pom;

    if (korijen==0) return 0;

    else if (strcmp(korijen->b.username,username)>0) korijen->lijevi=brisi(korijen->lijevi,username);
    else if (strcmp(korijen->b.username,username)<0) korijen->desni=brisi(korijen->desni,username);
    else if (korijen->lijevi==0)
    {
        pom=korijen->desni;
        free(korijen);
        return pom;
    }
    else if (korijen->desni==0)
    {
        pom=korijen->lijevi;
        free(korijen);
        return pom;
    }
    else
    {
        pom=najmanji(korijen->desni);
        korijen->b= pom->b;
        korijen->desni=brisi(korijen->desni,korijen->b.username);
    }
    return korijen;
}


void zaglavlje () //osnovno zaglavlje
{
    printf ("prezime         ime             username        pr.\n");
    printf ("=============== =============== =============== ===\n");
}

void inorder (CVOR *korijen) // sortiranje inorder
{
    if (korijen!=0)
        if (korijen!=0)
        {
            inorder(korijen->lijevi);
            printf ("%-15s %-15s %-15s  %c\n",korijen->b.prezime,korijen->b.ime,korijen->b.username,korijen->b.pr);
            inorder(korijen->desni);
        }
}



int trazi_bezpw (char *username,CVOR *korijen, int i)
{
    if (korijen==0) return 0;
    if (strcmp(username,korijen->b.username)==0)
    {
        ///sluzi za promjenu privilegije///
        if (i==1)
        {
            do
            {
                system("cls");
                printf ("Unesite username naloga kome mijenjate privilegiju: ");
                printf("%s\n", a.username);
                printf ("Unesite novu privilegiju (A-admin, N-nabavka, R-radnik): ");
                scanf ("\n%c",&a.pr);
            }
            while (a.pr!='A' && a.pr!='N' && a.pr!='R');
            korijen->b.pr=a.pr;
            if (strcmp(korijen->b.username,ulogovani)==0) priv=a.pr;
        }
        ///end priv///
        return 1;
    }
    else if (strcmp(username,korijen->b.username)<0) return trazi_bezpw (username,korijen->lijevi,i);
    else return trazi_bezpw (username,korijen->desni,i);
}

void menia() /// nije gotovo
{
    char izbor;
    int provjera;

    do
    {
    printf ("\t\t     Dobrodosli u administrativni panel!\n\n");
    Sleep(100);
    printf ("\t\tZa izbor pritisnite broj kraj zeljene opcije!\n");
        printf ("\n\t\t 1 Pregled zaposlenih");
        printf ("\n\t\t 2 Dodaj novog radnika\n");
        printf ("\t\t 3 Obrisi radnika\n");
        printf ("\t\t 4 Pregled statistike\n");
        printf ("\t\t 5 Izmjene sopstvenih informacija\n");
        printf ("\t\t 6 Mijenjanje privilegija radnika\n");
        printf ("\t\t 0 ODJAVA\n");
        izbor=izbor1();
        system("cls");
        if (izbor=='1')
        {
            system ("cls");
            zaglavlje();
            inorder(korijen);
            printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
            getch();
            system("cls");
        }
        if (izbor=='2')
        {
            system ("cls");
            korijen=dodaj(korijen,podaci(1));
        }
        else if (izbor=='3')
        {
            provjera=1;
            do
            {
                system ("cls");
                printf ("Unesite username osobe koju brisete: ");
                scanf ("%s",a.username);
                provjera=trazi_bezpw(a.username,korijen,0);
                if (provjera==0)
                {
                    printf ("Uneseni radnik ne postoji!");
                    Sleep(500);
                    system("cls");
                    printf ("Za dalje brisanje pritisnite 1: ");
                    scanf ("%d",&provjera);
                    provjera--;
                    system("cls");
                }
            }
            while (provjera==0);   // provjerava da li uneseni radnik postoji
            if (strcmp(a.username,ulogovani)!=0)
                korijen=brisi(korijen,a.username);
            else
            {
                printf ("Ne mozete obrisati samog sebe!");    /// moze se dodati do-while za pitanje ponovnog brisanja
                Sleep(1000);
                system("cls");
            }
        }
        else if (izbor=='4') { } ///treba zavrsiti
        else if (izbor=='5')
        {
            PromLicnihPod();
        }
        else if (izbor=='6')
        {
            system ("cls");
            printf ("Unesite username naloga kome mijenjate privilegiju: ");
            scanf ("%s",a.username);
            if(!(provjera=trazi_bezpw(a.username,korijen,0))) printf ("Username nije pronadjen");
            else trazi_bezpw(a.username,korijen,provjera);
            Sleep(100);
            system("cls");
        }
    }
    while (izbor!='0' && priv=='A') ;

}

