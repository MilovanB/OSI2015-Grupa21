#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include "clan.h"
int trazi_bezpw (char *username,CVOR *korijen, int i);
CVOR* najmanji(CVOR* korijen);
CVOR* brisi(CVOR *korijen, char* username);
void zaglavlje (); //osnovno zaglavlje
void inorder (CVOR *korijen); // sortiranje inorder
clanovi* podaci (int i);  // unos novog clana
CVOR* PromLicnihPod ();  // mijenjanje licnih podataka nekog clana
void menia(); /// nije gotovo



#endif // ADMIN_H_INCLUDED
