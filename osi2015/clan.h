#ifndef CLAN_H_INCLUDED
#define CLAN_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>


typedef struct {char username[15],pword[33],ime[15],prezime[15],pr;} clanovi;
typedef struct cvor {clanovi b; struct cvor *lijevi,*desni;} CVOR;
extern clanovi a;
extern CVOR *korijen;
extern char priv,ulogovani[20];
extern char imepreduzeca[25];

char izbor1();
int postoji (const char *); // provjera da li postoji datoteka
CVOR* novi (clanovi *a);
CVOR* dodaj (CVOR *korijen,clanovi *a);
CVOR* ucitaj_clanove (CVOR *korijen);
int trazi (char *username,char *password, CVOR *korijen);
char* sifra (); // zvijezdice
int login (); // logovanje    ostalo je jos centrirati
clanovi* podaci (int i);  // unos novog clana
CVOR* PromLicnihPod ();  // mijenjanje licnih podataka nekog clana
void brisistablo(CVOR*);


#endif // CLAN_H_INCLUDED
