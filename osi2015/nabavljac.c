#include "nabavljac.h"
NODE *root=0; // stablo za artikle
artikal art;
ptabela *roo=0; // lookup tabela, preko userername do pworda

//-----------------
char* generate() /// generisanje nasumicnih sifri za artikle
{
    char pom1[6];
    int i=0;
    pom1[0]=art.sifra[0]=art.vrsta[0];
    do{
        pom1[1]='0'+i;
        art.sifra[1]='0'+i;
        pom1[2]='5';
        pom1[3]=pom1[4]='0';
        pom1[5]=0;
        ++i;
    }while(trazi_sifra(pom1,root,0));///radi
    if (!trazi_sifra(pom1,root,1))
    {
     art.sifra[2]='5';
     art.sifra[3]=art.sifra[4]='0';
     art.sifra[5]=0;
    }///zavrseno
    else
    {do{
        srand(time(0));
        art.sifra[2]=rand()%10+'0';
        art.sifra[3]=rand()%10+'0';
        art.sifra[4]=rand()%10+'0';
        art.sifra[5]=0;
        strcpy(pom1,art.sifra);
    }while(trazi_sifra(pom1,root,1));}
    return art.sifra;
}
//----------------------------------------
int trazi_sifra(char *sifra, NODE *korijen, int i) // trazenje zadane osobe
{
    if(korijen==0) return 0;
    else if(!i && strcmp(art.vrsta,korijen->c.vrsta)==0 && strncmp(sifra,korijen->c.sifra,2)==0) return 0;
    ///printf("%s, %s\n",sifra, korijen->c.sifra);
    if(!i && (strcmp(art.vrsta,korijen->c.vrsta)!=0 && strncmp(sifra,korijen->c.sifra,2)==0)) return 1;
    else if(i && strcmp(sifra,korijen->c.sifra)==0) return 1;
    else if(strcmp(sifra, korijen->c.sifra)<0) return trazi_sifra(sifra,korijen->lijevi,i);
    else return trazi_sifra(sifra,korijen->desni,i);
}
//--------------------------------------------------------------------------------------

NODE* noviart (artikal *a)   // binarno stablo dodavanje cvora
{
    NODE *novi1=(NODE*)malloc(sizeof(NODE));
    novi1->lijevi=novi1->desni=0;
    novi1->c=*a;
    return novi1;
}
//------------------------------------------------------
ptabela* noviart2 (char *naziv, char *sifra) // dodavanje cvora u pomocnu tabelu
{
 ptabela *novi1=(ptabela*)malloc(sizeof(ptabela));
 novi1->lijevi=novi1->desni=0;
 strcpy(novi1->naziv,naziv);
 strcpy(novi1->sifra,sifra);
}
//-----------------------------------------------------------
ptabela* dodajart2 (ptabela *korijen,char *naziv, char* sifra) // dodavanje cvora u pomocnu tabelu
{
    if (korijen==0) return noviart2(naziv,sifra);
    if (strcmp(korijen->naziv,naziv)>0)
    korijen->lijevi=dodajart2(korijen->lijevi,naziv,sifra);
    else if (strcmp(korijen->naziv,naziv)<0) korijen->desni=dodajart2(korijen->desni,naziv,sifra);
    return korijen;
}
//------------------------------------------------------------------------------------------
NODE* dodajart (NODE *korijen,artikal *a) // dodavanje covra
{
    if (korijen==0) return noviart(a);
    if (strcmp(korijen->c.sifra,sifra)==0)
        korijen->c.kolicina+=a->kolicina;
   else if (strcmp(korijen->c.sifra,a->sifra)>0)
          korijen->lijevi=dodajart(korijen->lijevi,a);
    else  korijen->desni=dodajart(korijen->desni,a);
    return korijen;
}
//------------------------------------------------------------------------------
void zaglavljeart()///zaglavlje artikla
{
    printf("SIFRA NAZIV                KOLICINA MJERA CIJENA VRSTA");
    printf("\n===== ==================== ======== ===== ====== ===============");
}
//-------------------------------------------------------------------------------------
void inorderart(NODE* korijen)///ispis
{
    if(korijen!=0)
    {
      inorderart(korijen->lijevi);
        if (korijen->c.cijena!=0)
       printf("\n%-5s %-20s %8.2f %-5s %6.2f %-15s", korijen->c.sifra, korijen->c.naziv, korijen->c.kolicina, korijen->c.jedinica, korijen->c.cijena, korijen->c.vrsta);
      inorderart(korijen->desni);
    }
}
//---------------------------------------------------------------------------------------------------------------------
NODE* ucitaj_artikle (NODE *korijen) // ucitavanje iz datoteke i smijestanje u stablo
{
    FILE *dat;
    char c[1024];
dat= fopen ("ARTIKLI/artikli.txt","r");
    fgets(c,1024,dat);
    fgets(c,1024,dat);
    while(fscanf(dat,"%s %s %f %s %f %s", art.sifra, art.naziv, &art.kolicina,art.jedinica, &art.cijena, art.vrsta)==6)
    {
       roo=dodajart2(roo,art.naziv,art.sifra);
       korijen=dodajart(korijen,&art);
    }
    fclose(dat);
return korijen;
}
//-------------------------------------------------------------------------------------------
artikal* upis() // unosenje informacija o artiklima
{
    do{printf("KOLICINA: ");scanf("%f", &art.kolicina);}while(art.kolicina<0);
    printf("MJERA: ");scanf("%s",art.jedinica);
    strupr(art.jedinica);
    printf("VRSTA: ");scanf("%s", art.vrsta);
    strupr(art.vrsta);
    strcpy(art.sifra,generate());
    do{printf("CENA : ");scanf("%f", &art.cijena);}while(art.cijena<=0);

    return &art;
}
//----------------------------------------------------------------------------------
void upisart(FILE *dat) /// upisivanje u datoteku
{
     if (!postoji("ARTIKLI/artikli.txt"))
        {
            system("mkdir ARTIKLI"); ///kreira novi folder ako ne postoji
        }
     dat=fopen("ARTIKLI/artikli.txt","w");
     fprintf(dat,"SIFRA NAZIV                KOLICINA MJERA CIJENA VRSTA");
     fprintf(dat,"\n===== ==================== ======== ===== ====== ===============");
     fclose(dat);
}
//------------------------------------------------------------------------------------------------
void upisi(FILE *dat,NODE* korijen) // upisuje artikle u datoteku
{
    dat=fopen("ARTIKLI/artikli.txt","a");
if(korijen!=0)
    {
        fprintf(dat,"\n%-5s %-20s %8.2f %-4s %7.2f %-15s", korijen->c.sifra, korijen->c.naziv, korijen->c.kolicina,korijen->c.jedinica,korijen->c.cijena, korijen->c.vrsta);
        upisi(dat,korijen->lijevi);
        upisi(dat,korijen->desni);
    }
    fclose(dat);
}
//------------------------------------------------------------------------------------
NODE* traziposifri (char *sifra,NODE *korijen) /// trazi po sifri artikal
{
    if (korijen==0) return 0;
    if (strcmp(sifra,korijen->c.sifra)==0){strcpy(art.naziv,korijen->c.naziv); return korijen;}
    else if (strcmp(sifra,korijen->c.sifra)<0) return traziposifri (sifra,korijen->lijevi);
    else return traziposifri (sifra,korijen->desni);
}
//-------------------------------------------------------------------------------------------------
ptabela* brisiartikal2 (ptabela *korijen, char* naziv) /// brisanje cvora iz pomocne tabele
{
  ptabela *pom;

    if (korijen==0) return 0;

    else if (strcmp(korijen->naziv,naziv)>0) korijen->lijevi=brisiartikal2(korijen->lijevi,naziv);
    else if (strcmp(korijen->naziv,naziv)<0) korijen->desni=brisiartikal2(korijen->desni,naziv);
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
        pom=najmanjia2(korijen->desni);
        strcpy(korijen->naziv,pom->naziv);
        strcpy(korijen->sifra,pom->sifra);
        korijen->desni=brisiartikal2(korijen->desni,korijen->naziv);
    }

    return korijen;
}

//---------------------------------------------------------------------------------
ptabela* najmanjia2(ptabela* root) ///trazenje najmanjeg u pomocnoj tabeli
{
    while (root->lijevi != NULL) root=root->lijevi;
    return root;
}
//---------------------------------------------------------
NODE* brisiartikal(NODE *korijen, char* sifra) /// brisanje artikla iz stabla
{
    NODE *pom;

    if (korijen==0) return 0;

    else if (strcmp(korijen->c.sifra,sifra)>0) korijen->lijevi=brisiartikal(korijen->lijevi,sifra);
    else if (strcmp(korijen->c.sifra,sifra)<0) korijen->desni=brisiartikal(korijen->desni,sifra);
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
        pom=najmanjia(korijen->desni);
        korijen->c= pom->c;
        korijen->desni=brisiartikal(korijen->desni,korijen->c.sifra);
    }

    return korijen;
}
//-------------------------------------------------------------------
NODE* najmanjia(NODE* root) /// trazenje najmanjeg artikla
{
    while (root->lijevi != NULL) root=root->lijevi;
    return root;
}
//------------------------------------------------------------------------
int izmjenaartikla(char* sifra,NODE* korijen) // izmjena artikla
{
    if (korijen==0) return 0;
    if (strcmp(sifra,korijen->c.sifra)==0)
    {
        do
        {
        system("cls");
        printf("Unesite novu kolicinu artikla \"%s\" (stara kolicina %4.2f): ", korijen->c.naziv, korijen->c.kolicina);
        scanf("%f",&korijen->c.kolicina);
        }while(korijen->c.kolicina<0);
        printf("Unesite novu jedinicu mjere artikla \"%s\" (stara mjera %s): ",korijen->c.naziv, korijen->c.jedinica);
        scanf("%s",korijen->c.jedinica);
        strupr(korijen->c.jedinica);
        do
        {
        printf("Unesite novu cijenu artikla \"%s\" (stara cijena %4.2f): ", korijen->c.naziv, korijen->c.cijena);
        scanf("%f",&korijen->c.cijena);
        system("cls");
        }while(korijen->c.cijena==0);
        system("cls");
        return 1;
    }
    else if (strcmp(sifra,korijen->c.sifra)<0) return izmjenaartikla (sifra,korijen->lijevi);
    else return izmjenaartikla (sifra,korijen->desni);
}
//---------------------------------------------------------------------------------------------------
void menin() /// meni za nabavljaca
{
    FILE *dat;
    char izbor;
    int provjera;
    do
    {
         printf ("\t\t     Dobrodosli u panel za upravljanje robom!\n\n\t\t\t\b\b\bUlogovani ste kao: %s\n\n",ulogovani);
        Sleep(100);
        printf ("\t\tZa izbor pritisnite broj kraj zeljene opcije!\n");
        printf ("\n\t\t 1 Pregled robe");
        printf ("\n\t\t 2 Dodaj robu");
        printf ("\n\t\t 3 Brisi robu");
        printf ("\n\t\t 4 Izmjena robe");
        printf ("\n\t\t 9 Izmjena licnih informacija");
        printf ("\n\t\t 0 ODJAVA\n");
        izbor=izbor1();
        if (izbor=='1')
        {
            system("cls");
            zaglavljeart();
            inorderart(root);
            printf ("\n\nPritisnite bilo koje dugme za nastavak izvrsavanja programa...");
            getch();
            system("cls");
        }
        else if(izbor=='2')
        {
            system("cls");
            printf ("NAZIV: "); scanf ("%s",art.naziv);
            strupr(art.naziv);
            if (!trazipoimenu(art.naziv,roo)){
            root=dodajart(root,upis());
            roo=dodajart2(roo,art.naziv,art.sifra);
            system("cls");}
            else izmjenaartikla(art.sifra,root);
        }
        else if (izbor=='3')
        {
            provjera=1;
             do
            {
                system ("cls");
                printf ("Unesite ime artikla: ");
                scanf ("%s",art.naziv);
                strupr(art.naziv);
                provjera=trazipoimenu(art.naziv,roo);
                if (provjera==0)
                {
                    printf ("Uneseni artikal ne postoji!");
                    Sleep(1000);
                    system("cls");
                    printf ("Za dalje brisanje pritisnite 1: ");
                    provjera=(int)getch()-'0';
                    provjera--;
                    system("cls");
                }
                else {  traziposifri(art.sifra,root);
                        root=brisiartikal(root,art.sifra);
                        roo=brisiartikal2(roo,art.naziv);

                    }
         }while (provjera==0);
            system("cls");
         }

         else if(izbor=='4')
         {
             system("cls");
             printf ("Unesite ime artikla: ");
             scanf ("%s",art.naziv);
             strupr(art.naziv);
            if (trazipoimenu(art.naziv,roo)==0) {printf ("Artikal ne postoji!"); Sleep(600);}
            else {

                izmjenaartikla(art.sifra,root);
            }
            system("cls");
         }


        else if(izbor=='9')
        {
            PromLicnihPod();
            system("cls");
        }
    }while (izbor!='0');
    upisart(dat);
    upisi(dat,root);

}

//---------------------------------------------------------------------------------------
int trazipoimenu(char* naziv,ptabela* korijen) ///trazenje artikla po imenu
{
    if (korijen==0) return 0;
    if (strcmp(naziv,korijen->naziv)==0)
    {
        strcpy(art.sifra,korijen->sifra);
        return 1;
        }
    else if (strcmp(naziv,korijen->naziv)<0)  return trazipoimenu (naziv,korijen->lijevi);
    else return  trazipoimenu (naziv,korijen->desni);
}

//------------------------------------------------------------------------
void brisistabloart (NODE *korijen) ///brisanje cijelog stabla
{
    if (korijen!=0)
    {
        brisistabloart(korijen->lijevi);
        brisistabloart(korijen->desni);
        free(korijen);

    }
}
//-------------------------------------------------------------------
void brisistabloart2 (ptabela* korijen) /// brisanje cijele pomocne tabele
{
    if (korijen!=0)
    {
        brisistabloart2(korijen->lijevi);
        brisistabloart2(korijen->desni);
        free(korijen);

    }
}
