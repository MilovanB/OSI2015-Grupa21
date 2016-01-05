#ifndef NABAVLJAC_H_INCLUDED
#define NABAVLJAC_H_INCLUDED

#include "clan.h"

typedef struct
{
    char sifra[6],naziv[20],vrsta[15];
    float kolicina,cijena;
} artikal;

typedef struct node
{
    artikal c;
    struct node* lijevi, *desni;
} NODE;

extern NODE *root;
extern artikal art;

char izbor2();
NODE* noviart (artikal *a);
NODE* dodajart (NODE *korijen,artikal *a);
NODE* ucitaj_artikle (NODE *korijen);
void zaglavljeart();
void inorderart(NODE* korijen);

void menin();


#endif // NABAVLJAC_H_INCLUDED
