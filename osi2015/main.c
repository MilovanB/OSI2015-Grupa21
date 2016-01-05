#include "admin.h"
#include "nabavljac.h"


void glavnimeni ()
{
    if (priv=='A')
        menia();
    if (priv=='N')
        menin();
}

int main ()
{
    NODE *pom=0;
    korijen=ucitaj_clanove(korijen);
    root=ucitaj_artikle(pom);
    login();
    glavnimeni();
}

