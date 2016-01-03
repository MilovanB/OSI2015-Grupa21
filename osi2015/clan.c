#include "clan.h"
clanovi a;
CVOR *korijen=0;
char priv,ulogovani[20];

int postoji () // provjera da li postoji datoteka
{
    FILE *dat;
    if (dat=fopen("clanovi.txt","r"))
    {
        fclose(dat);
        return 1;
    }
    return 0;
}

CVOR* novi (clanovi *a)   // binarno stablo dodavanje prvog cvora
{
    CVOR *novi1=(CVOR*)malloc(sizeof(CVOR));
    novi1->lijevi=novi1->desni=0;
    novi1->b=*a;
    return novi1;
}

CVOR* dodaj (CVOR *korijen,clanovi *a) // dodavanje covra
{
    if (korijen==0) return novi(a);
    if (strcmp(korijen->b.username,a->username)>=0)
         korijen->lijevi=dodaj(korijen->lijevi,a);
    else  korijen->desni=dodaj(korijen->desni,a);
    return korijen;
}

CVOR* ucitaj_clanove (CVOR *korijen) // ucitavanje iz datoteke i smijestanje u stablo
{
    FILE *dat;
    char c[1024];
    if (!postoji())
        {
            dat=fopen("clanovi.txt","w");
            fprintf(dat,"rbr.    username         sifra                 ime                 prezime             pr.\n");
            fprintf(dat,"====    ===============  ===================   ===============     ===============     ===\n");
            fprintf(dat,"%d.      %-15s  %-19s   %-15s     %-15s      %c\n",1,"admin","admin","admin","admin",'A'); // prvo pravljenje
            fclose(dat);
        }
dat= fopen ("clanovi.txt","r");
    fgets(c,1024,dat);
    fgets(c,1024,dat);
    while ((fscanf (dat,"%*d. %s  %s  %s  %s %c",a.username,a.pword,a.ime,a.prezime,&a.pr))==5)  //ucitavanje u strukturu
    {
       korijen=dodaj(korijen,&a);
    }
    fclose(dat);
return korijen;
}

char* sifra () // zvijezdice
{
    int ch;
    char pword[32];
    int i=0;
    printf ("PASSWORD: ");
  fflush(stdout);

 while ((ch = getch()) != EOF && ch != '\n' && ch != '\r' && i < sizeof(pword) - 1)
  {
    if (ch == '\b' && i > 0)
    {
      printf("\b \b");
      fflush(stdout);
      i--;
      pword[i] = '\0';
    }
    else if (isalnum(ch))
    {
      putchar('*');
      pword[i++] = (char)ch;
    }
  }
  pword[i] = '\0';
  return pword;
}

void login () // logovanje    ostalo je jos centrirati
{
  int ch;
  char pword[32],username[15],pom[32];
  int i = 0,provjera;
  do {
        memset(username,0,sizeof username);
    printf ("USERNAME: ");
    gets (username);
    strcpy(pword,sifra());
 provjera=trazi(username,pword,korijen);
 system("cls");

 if (provjera==0)
 {
     system("COLOR C");
     printf ("Pogresan username/password!\n");
     Sleep(700);
     system ("cls");
     system("COLOR 7");
 }

} while (provjera==0);
strcpy(ulogovani,username);
}
int trazi (char *username,char *password, CVOR *korijen) // trazenje zadane osobe
{
    if (korijen==0) return 0;


     if (strcmp(username,korijen->b.username)==0 && (strcmp(password,korijen->b.pword)==0))
    {
        priv=korijen->b.pr;
        return 1;
    }
    else if (strcmp(username,korijen->b.username)<0) return trazi (username,password,korijen->lijevi);
    else return trazi (username,password,korijen->desni);
}
