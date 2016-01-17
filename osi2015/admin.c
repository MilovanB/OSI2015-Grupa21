#include "admin.h"




CVOR* najmanji(CVOR* korijen) ///najmanji cvor
{
    while (korijen->lijevi != NULL) korijen=korijen->lijevi;
    return korijen;
}
//-------------------------------------------------------------
CVOR* brisi(CVOR *korijen, char* username) ///brisanje cvora
{
    CVOR *pom;

    if (korijen==0) return 0;

    else if (strcmp(korijen->b.username,username)>0) korijen->lijevi=brisi(korijen->lijevi,username);
    else if (strcmp(korijen->b.username,username)<0) korijen->desni=brisi(korijen->desni,username);
    else if (korijen->lijevi==0)
    {
        pom=korijen->desni;
        free(korijen);
        return pom;
    }
    else if (korijen->desni==0)
    {
        pom=korijen->lijevi;
        free(korijen);
        return pom;
    }
    else
    {
        pom=najmanji(korijen->desni);
        korijen->b= pom->b;
        korijen->desni=brisi(korijen->desni,korijen->b.username);
    }
    return korijen;
}
///----------------------------------------------------------

void zaglavlje () //osnovno zaglavlje
{
    printf ("prezime         ime             username        pr.\n");
    printf ("=============== =============== =============== ===\n");
}
//--------------------------------
void inorder (CVOR *korijen) // sortiranje inorder
{
    if (korijen!=0)
        if (korijen!=0)
        {
            inorder(korijen->lijevi);
            printf ("%-15s %-15s %-15s  %c\n",korijen->b.prezime,korijen->b.ime,korijen->b.username,korijen->b.pr);
            inorder(korijen->desni);
        }
}

//-------------------------------

int trazi_bezpw (char *username,CVOR *korijen, int i) //trazenje clana preko username
{
    if (korijen==0) return 0;
    if (strcmp(username,korijen->b.username)==0)
    {
        ///sluzi za promjenu privilegije///
        if (i==1)
        {
            do
            {
                system("cls");
                printf ("Unesite username naloga kome mijenjate privilegiju: ");
                printf("%s\n", a.username);
                printf ("Unesite novu privilegiju (A-admin, N-nabavka, R-radnik): ");
                scanf ("\n%c",&a.pr);
            }
            while (a.pr!='A' && a.pr!='N' && a.pr!='R');
            korijen->b.pr=a.pr;
            if (strcmp(korijen->b.username,ulogovani)==0) priv=a.pr;
        }
        ///end priv///
        return 1;
    }
    else if (strcmp(username,korijen->b.username)<0) return trazi_bezpw (username,korijen->lijevi,i);
    else return trazi_bezpw (username,korijen->desni,i);
}
//--------------------------------------
void menia() /// meni administratora
{
    char izbor;
    int provjera;
    FILE* dat;
    do
    {
    printf ("\t\t     Dobrodosli u administrativni panel!\n\n\t\t\t\b\b\bUlogovani ste kao: %s\n\n",ulogovani);
    Sleep(100);
    printf ("\t\tZa izbor pritisnite broj kraj zeljene opcije!\n");
        printf ("\n\t\t 1 Pregled zaposlenih");
        printf ("\n\t\t 2 Dodaj novog radnika\n");
        printf ("\t\t 3 Obrisi radnika\n");
        printf ("\t\t 4 Pregled statistike\n");
        printf ("\t\t 5 Mijenjanje privilegija radnika\n");
        printf ("\t\t 9 Izmjene sopstvenih informacija\n");
        printf ("\t\t 0 ODJAVA\n");
        izbor=izbor1();
        system("cls");
        if (izbor=='1')
        {
            system ("cls");
            zaglavlje();
            inorder(korijen);
            printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
            getch();
            system("cls");
        }
        if (izbor=='2')
        {
            system ("cls");
            korijen=dodaj(korijen,podaci(1));
        }
        else if (izbor=='3')
        {
            provjera=1;
            do
            {
                system ("cls");
                printf ("Unesite username osobe koju brisete: ");
                scanf ("%s",a.username);
                provjera=trazi_bezpw(a.username,korijen,0);
                if (provjera==0)
                {
                    printf ("Uneseni radnik ne postoji!");
                    Sleep(500);
                    system("cls");
                    printf ("Za dalje brisanje pritisnite 1: ");
                    scanf ("%d",&provjera);
                    provjera--;
                    system("cls");
                }
            }
            while (provjera==0);   // provjerava da li uneseni radnik postoji
            if (strcmp(a.username,ulogovani)!=0)
                korijen=brisi(korijen,a.username);
            else
            {
                printf ("Ne mozete obrisati samog sebe!");    /// moze se dodati do-while za pitanje ponovnog brisanja
                Sleep(1000);
                system("cls");
            }
        }
        else if (izbor=='4') {  ///izvjestaji
                system("cls");
                char ch, datum[20], buf[100], godina[6], mjesec[3],dan[3];
                NODE* pom=0;
                printf("\t\t\tPritisnite broj kraj zeljene opcije\n\n");
                printf("\t\t\t\t\b\b\b1 Dnevna statistika\n\t\t\t\t\b\b\b2 Mjesecna statistika\n\t\t\t\t\b\b\b3 Godisnja statistika\n");
                ch=izbor1();
                system("cls");
                if(ch=='1') /// izvjestaj dnevni
                {
                    printf("\t Unesite datum za koji zelite da pregledate statistiku \n\n\t\t\t(format dd-mm-gggg): ");
                    scanf("%s", datum);
                    mjesec[0]=datum[3];
                    mjesec[1]=datum[4];
                    mjesec[2]=0;
                    strcpy(godina,&datum[6]);
                    strcpy(buf,"IZVJESTAJ/");
                    strcat(buf,godina);
                    strcat(buf,"/");
                    strcat(buf,mjesec);
                    strcat(buf,"/ ");
                    strcat(buf,datum);
                    strcat(buf,".txt");
                    if(dat=fopen(buf,"r")){
                    system("cls");
                    fgets(buf,sizeof buf,dat);
                    printf("%s\n",buf);
                    fgets(buf,sizeof buf,dat);
                    printf("%s\n\n",buf);
                    fgets(buf,sizeof buf,dat);fgets(buf,sizeof buf,dat);fgets(buf,sizeof buf,dat);
                    while(fscanf(dat,"%s %s %f %s %f %s", art.sifra, art.naziv, &art.kolicina,art.jedinica, &art.cijena, art.vrsta)==6)
                        pom=dodajart(pom,&art);
                    fclose(dat);

                    zaglavljeart();
                    inorderart(pom);}
                    else {printf ("\nNema podataka za uneseni datum!");}
                    printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
                getch();
                }
                else if(ch=='2') ///mjesecni
                {
                    printf("\tUnesite mjesec i godinu za koji zelite da pregledate statistiku\n\n\t\t\t(format: mm-gggg): ");
                    scanf("%s",datum);
                    mjesec[0]=datum[0];
                    mjesec[1]=datum[1];
                    mjesec[2]=0;
                    strcpy(godina,&datum[3]);
                    strcpy(dan,"01");
                    do
                    {
                        strcpy(buf,"IZVJESTAJ/");
                        strcat(buf,godina);
                        strcat(buf,"/");
                        strcat(buf,mjesec);
                        strcat(buf,"/ ");
                        strcat(buf,dan);
                        strcat(buf,"-");
                        strcat(buf,datum);
                        strcat(buf,".txt");
                        dat=fopen(buf,"r");

                        fgets(buf,sizeof buf,dat);
                        fgets(buf,sizeof buf,dat);
                        fgets(buf,sizeof buf,dat);fgets(buf,sizeof buf,dat);fgets(buf,sizeof buf,dat);
                        while(fscanf(dat,"%s %s %f %s %f %s", art.sifra, art.naziv, &art.kolicina,art.jedinica, &art.cijena, art.vrsta)==6)
                        {
                            NODE* temp=traziposifri(art.sifra,pom);
                            if(temp&& art.cijena == temp->c.cijena) temp->c.kolicina+=art.kolicina;
                            else pom=dodajart(pom,&art);
                        }
                        fclose(dat);
                        dan[1]++;
                        if(dan[1]>'9'){dan[1]-=10;dan[0]++;}
                    }while(strcmp(dan,"32")<0);
                    if (pom==0) printf ("\nNema podataka za uneseni datum!");
                    else{
                    zaglavljeart();
                    inorderart(pom);}
                    printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
                    getch();
                }
                else if(ch=='3') ///godisnji
                {
                    printf("\t\t\bUnesite godinu za koju zelite da pregledate statistiku \n\n\t\t\t (format gggg): ");
                    scanf("%s",godina);
                    system("cls");
                    printf("UCITAVANJE, MOLIM SACEKAJTE!\n");
                    strcpy(mjesec,"01");
                    strcpy(dan,"01");
                    do{
                        strcpy(dan,"01");
                        do
                        {

                        strcpy(buf,"IZVJESTAJ/");
                        strcat(buf,godina);
                        strcat(buf,"/");
                        strcat(buf,mjesec);
                        strcat(buf,"/ ");
                        strcat(buf,dan);
                        strcat(buf,"-");
                        strcat(buf,mjesec);
                        strcat(buf,"-");
                        strcat(buf,godina);
                        strcat(buf,".txt");
                        dat=fopen(buf,"r");
                        fgets(buf,sizeof buf,dat);
                        fgets(buf,sizeof buf,dat);
                        fgets(buf,sizeof buf,dat);fgets(buf,sizeof buf,dat);fgets(buf,sizeof buf,dat);
                        while(fscanf(dat,"%s %s %f %s %f %s", art.sifra, art.naziv, &art.kolicina,art.jedinica, &art.cijena, art.vrsta)==6)
                        {
                            NODE* temp=traziposifri(art.sifra,pom);
                            if(temp&& art.cijena == temp->c.cijena) temp->c.kolicina+=art.kolicina;
                            else pom=dodajart(pom,&art);
                        }
                        fclose(dat);
                        dan[1]++;
                        if(dan[1]>'9'){dan[1]-=10;dan[0]++;}
                        }while(strcmp(dan,"32")<0);
                        mjesec[1]++;
                        if(mjesec[1]>'9'){mjesec[1]-=10;mjesec[0]++;}
                    }while(strcmp(mjesec,"13")<0);
                    system("cls");
                     printf("\t\t\bUnesite godinu za koju zelite da pregledate statistiku \n\n\t\t\t (format gggg): ");
                    printf("%s\n\n",godina);
                    if (pom==0) printf ("\nNema podataka za uneseni datum!");
                    else{zaglavljeart();
                    inorderart(pom);
                    }
                   printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
                getch();
                }
                system("cls");
             brisistabloart(pom);

        } ///po vrstama da ispisuje
        else if (izbor=='9')
        {
            PromLicnihPod();
        }
        else if (izbor=='5')
        {
            system ("cls");
            printf ("Unesite username naloga kome mijenjate privilegiju: ");
            scanf ("%s",a.username);
            if(!(provjera=trazi_bezpw(a.username,korijen,0))) printf ("Username nije pronadjen");
            else trazi_bezpw(a.username,korijen,provjera);
            Sleep(100);
            system("cls");
        }
    }
    while (izbor!='0' && priv=='A');
    upisclan();
    upisiclan(korijen);

}
///------------------------------------------------------
void upisclan () /// upisivanje zaglavnja u datoteku
{
     FILE *dat;
     dat=fopen("CLANOVI/clanovi.txt","w");
     fprintf(dat,"username         sifra                  ime                 prezime             pr.\n");
     fprintf(dat,"===============  ====================   ===============     ===============     ===");
     fclose(dat);
}
//-------------------------------------------------------------------------
void upisiclan (CVOR* korijen)  /// upisivanje clanova u datoteku
{
    FILE *dat;
     dat=fopen("CLANOVI/clanovi.txt","a");
if(korijen!=0)
    {
        fprintf(dat,"\n%-15s  %-20s   %-15s     %-15s      %c",korijen->b.username, korijen->b.pword, korijen->b.ime,korijen->b.prezime,korijen->b.pr);

        upisiclan(korijen->lijevi);
        upisiclan(korijen->desni);
    }
    fclose(dat);
}
