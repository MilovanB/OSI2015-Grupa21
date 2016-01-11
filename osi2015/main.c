#include "admin.h"
#include "nabavljac.h"
#include "radnik.h"

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
    NODE *pom=0;
    korijen=ucitaj_clanove(korijen);
    root=ucitaj_artikle(pom);
    login();
    glavnimeni();
}

