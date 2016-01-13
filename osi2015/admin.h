#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include "clan.h"
char izbor1();
int trazi_bezpw (char *,CVOR *, int );
CVOR* najmanji(CVOR* );
CVOR* brisi(CVOR * ,char*);
void upisiclan (CVOR* );
void upisclan ();
void zaglavlje (); //osnovno zaglavlje
void inorder (CVOR *); // sortiranje inorder
void menia(); /// nije gotovo



#endif // ADMIN_H_INCLUDED
