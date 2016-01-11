#include "clan.h"
clanovi a;
CVOR *korijen=0;
char priv,ulogovani[20];
char imepreduzeca[25];


int postoji (const char *str) // provjera da li postoji datoteka
{              ///napraviti da prima const char * da bi sluzilo i za artikle
    FILE *dat;
    if (dat=fopen(str,"r"))  ///dat=fopen(const char* ,"r")
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
    if (!postoji("CLANOVI/clanovi.txt"))
        {
            system("mkdir CLANOVI"); ///kreira novi folder ako ne postoji
            dat=fopen("CLANOVI/clanovi.txt","w");
            fprintf(dat,"rbr.    username         sifra                 ime                 prezime             pr.\n");
            fprintf(dat,"====    ===============  ===================   ===============     ===============     ===\n");
            printf ("Dobrodosli u softver!");
            system("COLOR F");
            printf (" Molimo Vas unesite ime Vase prodavnice: ");
            gets(imepreduzeca);
            system("cls");
            printf ("Jos samo par koraka i Vasa prodavnica '%s' je spremna za koristenje!\n\n",imepreduzeca);
            Sleep(100);
            printf ("Za prvo pokretanje programa potrebno je kreirati novog administratora!\n");
            korijen=dodaj(korijen,podaci(0));
            korijen->b.pr='A';
            system ("cls");
            fclose(dat);
        }
dat= fopen ("CLANOVI/clanovi.txt","r");
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
    if (ch == '\b' && i > 0 )
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
      printf ("\n\n\n\n\n\n\n\n\n\n\n");
        memset(username,0,sizeof username);
        system("COLOR F");
        fflush(stdin);
    printf ("\t\t\t\tUSERNAME: ");
    gets (username);
    printf ("\t\t\t\t");
    strcpy(pword,sifra());
 provjera=trazi(username,pword,korijen);
 system("cls");

 if (provjera==0)
 {
     system("COLOR C");
     printf ("\n\n\n\n\n\n\n\n\n\n\n");
     printf ("\t\t\tPogresan username/password!\n");
     Sleep(800);
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

clanovi* podaci (int i)  // unos novog clana
{
    char password[32];
    int provjera,pomocna=0;
    do
    {
        printf ("\nUSERNAME: ");
        scanf ("%s",a.username);
        provjera=trazi_bezpw (a.username,korijen,1);
        if (provjera==1)
        {
            system ("COLOR C");
            printf ("Ovaj username vec postoji!");
            Sleep(500);
            system("cls");
            system("COLOR 7");
        }
    }
    while (provjera==1);
    do
    {
        if (pomocna!=0)
        {
            system ("cls");
            printf ("USERNAME: %s\n",a.username);
        }
        strcpy(password,sifra());
        printf ("\nPONOVITE ");
        strcpy(a.pword,sifra());
        pomocna=strcmp(a.pword,password);
    }
    while (pomocna!=0);

    printf ("\nIME: ");
    scanf ("%s",a.ime);
    printf ("PREZIME:");
    scanf ("%s",a.prezime);
    if (i==1) do
        {
            system ("cls");
            printf ("Unesite privilegiju radnika (A-admin, N-nabavka, R-radnik): ");
            scanf ("%c",&a.pr);
        }
        while (a.pr!='A' && a.pr!='N' && a.pr!='R');
    else
    {
        a.pr = priv;
    }
system("cls");
    return &a;
}

CVOR* PromLicnihPod ()  // mijenjanje licnih podataka nekog clana
{
    char pom[20];
    system ("cls");
    printf ("Za promjenu informacija unesite stari ");
    strcpy(a.pword,sifra());
    if (trazi(ulogovani,a.pword,korijen))
    {
        strcpy(pom,ulogovani);
        memset(ulogovani,0,sizeof(ulogovani));
        korijen=brisi(korijen,pom);
        korijen=dodaj(korijen,podaci(0));
        strcpy(ulogovani,a.username);
    }
    else system ("cls");

}
