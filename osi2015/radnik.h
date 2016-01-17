#ifndef RADNIK_H_INCLUDED
#define RADNIK_H_INCLUDED

#include "clan.h"
#include "nabavljac.h"


typedef struct{
artikal *niz;
int i;
float cijena;
} KORPA;


extern KORPA korp;
extern int brracuna;
void menir();
void prodaja();



#endif // RADNIK_H_INCLUDED
