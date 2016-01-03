#include "admin.h"


void glavnimeni ()
{
    if (priv=='A')
        menia();
    //if (priv=='N')
      //  menin();


}

int main ()
{

    korijen=ucitaj_clanove(korijen);
    login();
    glavnimeni();

}

