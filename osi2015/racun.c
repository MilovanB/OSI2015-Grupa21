#include "racun.h"
float ucijena=0; // ukupna cijena
NODE izvjestaj;  /// cvor za izvjestaj

int pisiracun (KORPA *a) ///stampanje raucna
{

    FILE *dat;
    char racun[20]="racun br";
    static char ex[5]=".txt";
    char r[10];
    char pom[10];
    time_t now;
    struct tm *ts;
    char buf[80];
    now =time(NULL);
    sprintf(r,"%d",brracuna);
    strcat(racun,r);
    strcat(racun,ex);
    strcpy(r,"RACUNI/");
    strcat(r,racun);
    system ("mkdir RACUNI");
    dat=fopen(r,"w");
    ts=localtime(&now);
    strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", ts);
     fprintf(dat,"============================\n");
     fprintf(dat,"%*s%*s   \n",14+strlen(imepreduzeca)/2,imepreduzeca,14-strlen(imepreduzeca)/2,"");
     fprintf(dat,"      78000 BANJA LUKA      \n");
     fprintf(dat,"----------------------------\n");
     fprintf(dat,"        MALOPRODAJNI        \n");
     fprintf(dat,"       FISKALNI RACUN       \n");
     fprintf(dat,"----------------------------\n");
     for (int i=0;i<a->i-1;i++)
     {
     fprintf(dat,"%-20s   %-5s                \n",a->niz[i].naziv,a->niz[i].jedinica);
     fprintf(dat,"%7.2f x %6.2f    %8.2f\n",a->niz[i].kolicina,a->niz[i].cijena,a->niz[i].kolicina*a->niz[i].cijena);
     }
     fprintf(dat,"----------------------------\n");
     fprintf(dat,"PDV:                     17%\n");
     fprintf(dat,"Cijena bez PDV:     %8.2f\n",a->cijena/1.17);
     fprintf(dat,"Iznos PDV:          %8.2f\n",a->cijena-(a->cijena/1.17));
     fprintf(dat,"ZA UPLATU:          %8.2f\n",a->cijena);
     fprintf(dat,"----------------------------\n");
     fputs(buf,dat);
     fprintf(dat,"\nBRAC:%05d   %-14s\n",brracuna++,ulogovani);
     fprintf(dat,"----------------------------\n");
     fprintf(dat,"   *HVALA NA POVJERENJU*    \n");
     fprintf(dat,"%*s%*s   \n",14+strlen(imepreduzeca)/2,imepreduzeca,14-strlen(imepreduzeca)/2,"");
     fprintf(dat,"============================\n");
     SetFileAttributes(r,FILE_ATTRIBUTE_READONLY);
     fclose(dat);
     return 12;
}

void dizvjestaj (artikal a) /// dnevni izvjestaj, preko kojeg se rade svi ostali
{

    NODE *pom=0;
    if((pom=traziposifri(a.sifra,&izvjestaj))==0)
    {
    dodajart(&izvjestaj,&a);
    }
    else pom->c.kolicina+=a.kolicina;
    ucijena+=a.cijena*a.kolicina;
}

void krajsmjene(NODE *korijen) /// zavrsavanje izvjestaja pri izlasku iz programa
{
    FILE* dat;
     time_t     now;
     int i;
    struct tm *ts;
    char buf[80],datum[80],putanja[100];
    char mjesec[3];
    char godina[6];
    now = time(NULL);
    ts = localtime(&now);
    strftime(buf, sizeof(buf), " %d-%m-%Y", ts);
    strcpy(datum,buf);
    mjesec[0]=buf[4];
    mjesec[1]=buf[5];
    mjesec[2]=0;
    strcpy(godina,&buf[7]);
    strcat(buf,".txt");
    mkdir ("IZVJESTAJ");
    strcpy(putanja,"IZVJESTAJ/");
     strcat(putanja,godina);
    mkdir (putanja);
    strcat(putanja,"/");
    strcat(putanja,mjesec);
    mkdir(putanja);
    strcat(putanja,"/");
    strcat(putanja,buf);

    SetFileAttributes(putanja,FILE_ATTRIBUTE_NORMAL);
    dat=fopen(putanja,"w");
     fprintf(dat,"Izvjestaj za %s - pazar: %.2f\n",datum,ucijena);
     fprintf(dat,"--------------------------------------------\n\n");
     fprintf(dat,"SIFRA NAZIV                KOLICINA MJERA CIJENA VRSTA");
     fprintf(dat,"\n===== ==================== ======== ===== ====== ===============");
        fclose(dat);

    isracun(&izvjestaj,dat,putanja);

SetFileAttributes(putanja,FILE_ATTRIBUTE_READONLY);
    return 0;
}


void isracun(NODE *korijen,FILE* dat,char* putanja) ///upis racuna u datoteke
{
    dat=fopen(putanja,"a");
    if(korijen!=0)
    {
        if (korijen->c.cijena!=0)
        fprintf(dat,"\n%-5s %-20s %8.2f %-4s %7.2f %-15s", korijen->c.sifra, korijen->c.naziv, korijen->c.kolicina,korijen->c.jedinica,korijen->c.cijena, korijen->c.vrsta);
        isracun(korijen->lijevi,dat,putanja);
        isracun(korijen->desni,dat,putanja);
    }
    fclose(dat);
}
