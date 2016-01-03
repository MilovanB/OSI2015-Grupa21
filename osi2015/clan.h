#ifndef CLAN_H_INCLUDED
#define CLAN_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>

typedef struct {char username[15],pword[19],ime[15],prezime[15],pr;} clanovi;
typedef struct cvor {clanovi b; struct cvor *lijevi,*desni;} CVOR;
extern clanovi a;
extern CVOR *korijen;
extern char priv,ulogovani[20];

int postoji (); // provjera da li postoji datoteka
CVOR* novi (clanovi *a);
CVOR* dodaj (CVOR *korijen,clanovi *a);
CVOR* ucitaj_clanove (CVOR *korijen);
int trazi (char *username,char *password, CVOR *korijen);
char* sifra (); // zvijezdice
void login (); // logovanje    ostalo je jos centrirati



#endif // CLAN_H_INCLUDED