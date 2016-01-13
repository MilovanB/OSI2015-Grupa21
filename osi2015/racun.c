#include "racun.h"

int pisiracun (KORPA *a)
{

    FILE *dat;
    dat=fopen("pomocna.txt","r");
    fscanf(dat,"%d",&brracuna);
    fclose(dat);
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
