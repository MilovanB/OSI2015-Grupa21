#ifndef NABAVLJAC_H_INCLUDED
#define NABAVLJAC_H_INCLUDED

#include <time.h>
#include "clan.h"

typedef struct
{
    char sifra[6],naziv[20],vrsta[15],jedinica[5];
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
char* generate();
int trazi_sifra(char *sifra, NODE *korijen, int i);
NODE* noviart (artikal *a);
NODE* najmanjia(NODE* root);
int izmjenaartikla(NODE* root,artikal* a);
NODE* brisiartikal(NODE* korijen,char* sifra);
NODE* dodajart (NODE *korijen,artikal *a);
NODE* ucitaj_artikle (NODE *korijen);
NODE* traziposifri (char *sifra,NODE *korijen);
void zaglavljeart();
void inorderart(NODE* korijen);

void menin();


#endif // NABAVLJAC_H_INCLUDED
