#ifndef RACUN_H_INCLUDED
#define RACUN_H_INCLUDED
#include "radnik.h"
#include "clan.h"
extern float cijena;
extern NODE izvjestaj;
int pisiracun(KORPA*);
void dizvjestaj(artikal);
void krajsmjene(NODE*);
void isracun(NODE*,FILE*,char*);

#endif // RACUN_H_INCLUDED
