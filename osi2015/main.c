#include "admin.h"
#include "nabavljac.h"
#include "radnik.h"
#include "racun.h"

void glavnimeni ()
{
    if (priv=='A')
        menia();
    if (priv=='N')
        menin();
    if (priv=='R')
        menir();
}

int main ()
{
    char c;
    int i=1;
    korijen=ucitaj_clanove(korijen);
    root=ucitaj_artikle(root);
    do{
    system("cls");
    i=login();
    glavnimeni();
    system("cls");
    if (i) {printf ("Za vracanje u login pritisnite D, ili bilo koji drugi znak za kraj programa:");
    c=getch();}
    }while (c=='D' || c=='d' && i);
    system("cls");

    krajsmjene(&izvjestaj);
    brisistabloart(root);
    brisistabloart2(roo);
    brisistablo(korijen);
    brisistabloart(&izvjestaj);
}

