#ifndef NABAVLJAC_H_INCLUDED
#define NABAVLJAC_H_INCLUDED

#include <time.h>
#include "clan.h"

typedef struct loo
{
    char sifra[6],naziv[20];
    struct loo *lijevi, *desni;

} ptabela; //pomocna tabela

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
extern ptabela *roo;

char izbor2();
char* generate();
int trazi_sifra(char *sifra, NODE *korijen, int i);
NODE* noviart (artikal *a);
NODE* najmanjia(NODE* root);
int izmjenaartikla(char*,NODE*);
NODE* brisiartikal(NODE* korijen,char* sifra);
NODE* dodajart (NODE *korijen,artikal *a);
NODE* ucitaj_artikle (NODE *korijen);
NODE* traziposifri (char *sifra,NODE *korijen);
void zaglavljeart();
void inorderart(NODE* korijen);
ptabela* noviart2(char*,char*);
ptabela* dodajart2(ptabela*,char*,char*);
ptabela* najmanjia2(ptabela*);
ptabela* brisiartikal2(ptabela*,char*);
int trazipoimenu(char*,ptabela*);
void menin();


#endif // NABAVLJAC_H_INCLUDED
