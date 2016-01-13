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
    korijen=ucitaj_clanove(korijen);
    root=ucitaj_artikle(root);
    login();
    glavnimeni();
}

