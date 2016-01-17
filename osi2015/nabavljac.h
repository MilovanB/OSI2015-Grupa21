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

char* generate();
int trazi_sifra(char* , NODE*, int);
NODE* noviart (artikal*);
NODE* najmanjia(NODE*);
int izmjenaartikla(char*,NODE*);
NODE* brisiartikal(NODE*,char*);
NODE* dodajart (NODE*,artikal*);
NODE* ucitaj_artikle (NODE *);
NODE* traziposifri (char *,NODE *);
void brisistabloart(NODE*);
void zaglavljeart();
void inorderart(NODE*);
ptabela* noviart2(char*,char*);
ptabela* dodajart2(ptabela*,char*,char*);
ptabela* najmanjia2(ptabela*);
ptabela* brisiartikal2(ptabela*,char*);
void brisistabloart2(ptabela*);
int trazipoimenu(char*,ptabela*);
void menin();


#endif // NABAVLJAC_H_INCLUDED
