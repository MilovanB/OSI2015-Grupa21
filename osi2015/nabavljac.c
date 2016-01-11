#include "nabavljac.h"
NODE *root=0;
artikal art;

char izbor2()
{
    fflush(stdout);
    return getch();
}

char* generate()
{
    char pom1[5];
    int i=-1;
    pom1[0]=art.sifra[0]=art.vrsta[0];
    do{
        i++;
        pom1[1]='0'+i;
        art.sifra[1]='0'+i;
        pom1[2]='5';
        pom1[3]=pom1[4]='0';
    }while(trazi_sifra(pom1,root,0));///radi
    if (!trazi_sifra(pom1,root,1))
    {
     art.sifra[2]='5';
     art.sifra[3]=art.sifra[4]='0';
    }///zavrseno
    if(trazi_sifra(pom1,root,1))
    {do{
        srand(time(0));
        art.sifra[2]=rand()%10+'0';
        art.sifra[3]=rand()%10+'0';
        art.sifra[4]=rand()%10+'0';
        strcpy(pom1,art.sifra);
    }while(trazi_sifra(pom1,root,1));}
    return art.sifra;
}

int trazi_sifra(char *sifra, NODE *korijen, int i) // trazenje zadane osobe
{
    if(!i && (korijen==0 || strcmp(art.vrsta,korijen->c.vrsta)==0)) return 0;
    else if (korijen==0) return 0;
    if(!i && strncmp(sifra,korijen->c.sifra,2)==0)
    {
        return 1;
    }
    else
        if (strcmp(sifra,korijen->c.sifra)==0)
    {
        return 1;
    }
    else if (strcmp(sifra,korijen->c.sifra)<0) return trazi_sifra (sifra,korijen->lijevi,i);
    else return trazi_sifra (sifra,korijen->desni,i);
}


NODE* noviart (artikal *a)   // binarno stablo dodavanje prvog cvora
{
    NODE *novi1=(NODE*)malloc(sizeof(NODE));
    novi1->lijevi=novi1->desni=0;
    novi1->c=*a;
    return novi1;
}

NODE* dodajart (NODE *korijen,artikal *a) // dodavanje covra
{
    if (korijen==0) return noviart(a);
    if (strcmp(korijen->c.sifra,a->sifra)>=0)
          korijen->lijevi=dodajart(korijen->lijevi,a);
    else  korijen->desni=dodajart(korijen->desni,a);
    return korijen;
}


void zaglavljeart()///zaglavlje artikla
{
    printf("SIFRA NAZIV                KOLICINA MJERA CIJENA VRSTA");
    printf("\n===== ==================== ======== ===== ====== ===============");
}


void inorderart(NODE* korijen)///ispis
{
    if(korijen!=0)
    {
      inorderart(korijen->lijevi);
      printf("\n%-5s %-20s %8.2f %-5s %6.2f %-15s", korijen->c.sifra, korijen->c.naziv, korijen->c.kolicina, korijen->c.jedinica, korijen->c.cijena, korijen->c.vrsta);
      inorderart(korijen->desni);
    }
}

NODE* ucitaj_artikle (NODE *korijen) // ucitavanje iz datoteke i smijestanje u stablo
{
    FILE *dat;
    char c[1024];
    /*if (!postoji("ARTIKLI/artikli.txt"))
        {
            system("mkdir ARTIKLI"); ///kreira novi folder ako ne postoji
            dat=fopen("ARTIKLI/artikli.txt","w");
            fclose(dat);
        }*/
dat= fopen ("ARTIKLI/artikli.txt","r");
    fgets(c,1024,dat);
    fgets(c,1024,dat);
    while(fscanf(dat,"%s %s %f %s %f %s", art.sifra, art.naziv, &art.kolicina,art.jedinica, &art.cijena, art.vrsta)==6)
    {
       korijen=dodajart(korijen,&art);
    }
    fclose(dat);
return korijen;
}

artikal* upis()
{
    system("cls");
    printf("NAZIV: ");scanf("%s", art.naziv);
    printf("KOLICINA: ");scanf("%f", &art.kolicina);
    printf("MJERA: ");scanf("%s",art.jedinica);
    printf("CENA : ");scanf("%f", &art.cijena);
    printf("VRSTA: ");scanf("%s", art.vrsta);
    strcpy(art.sifra,generate());
    system("cls");
    return &art;
}

void upisart(FILE *dat)
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

void upisi(FILE *dat,NODE* korijen)
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

NODE* traziposifri (char *sifra,NODE *korijen)
{
    if (korijen==0) return 0;
    if (strcmp(sifra,korijen->c.sifra)==0) return korijen;
    else if (strcmp(sifra,korijen->c.sifra)<0) return traziposifri (sifra,korijen->lijevi);
    else return traziposifri (sifra,korijen->desni);
}

NODE* brisiartikal(NODE *korijen, char* sifra)
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


NODE* najmanjia(NODE* root)
{
    while (root->lijevi != NULL) root=root->lijevi;
    return root;
}

int izmjenaartikla(NODE* korijen,artikal* a)
{
    if (strcmp(a->sifra,korijen->c.sifra)==0)
    {
        korijen->c.cijena=a->cijena;
        strcpy(korijen->c.naziv,a->naziv);
        strcpy(korijen->c.vrsta,a->vrsta);
        strcpy(korijen->c.jedinica,a->jedinica);
        korijen->c.kolicina=a->kolicina;
    }
    else if (strcmp(sifra,korijen->c.sifra)<0) return izmjenaartikla (korijen->lijevi,a);
    else return izmjenaartikla (korijen->desni,a);
}




void menin()
{
    FILE *dat;
    char izbor;
    int provjera;
    printf ("\t\t     Dobrodosli u panel za upravljanje robom!\n\n");
    Sleep(100);
    printf ("\t\tZa izbor pritisnite broj kraj zeljene opcije!\n");
    do
    {
        printf ("\n\t\t 1 Pregled robe");
        printf ("\n\t\t 2 Dodaj robu");
        printf ("\n\t\t 3 Brisi robu");
        printf ("\n\t\t 4 Izmjena robe");
        printf ("\n\t\t 9 Izmjena licnih informacija");
        printf ("\n\t\t 0 ODJAVA\n");
        izbor=izbor2();
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
            root=dodajart(root,upis());
            system("cls");
        }
        else if (izbor=='3')
        {
            provjera=1;
             do
            {
                system ("cls");
                printf ("Unesite sifru artikla: ");
                scanf ("%s",art.sifra);
                provjera=traziposifri(art.sifra,root);
                if (provjera==0)
                {
                    printf ("Unesena sifra ne postoji!");
                    Sleep(500);
                    system("cls");
                    printf ("Za dalje brisanje pritisnite 1: ");
                    scanf ("%d",&provjera);
                    provjera--;
                    system("cls");
                }
                else {root=brisiartikal(root,art.sifra);}
         }while (provjera==0);
            system("cls");
         }

         else if(izbor=='4')
         {
             printf ("Unesite sifru artikla: ");
             scanf ("%s",art.sifra);
            if (traziposifri(art.sifra,root)==0) {printf ("Sifra ne postoji!"); Sleep(600);}
            else {

                izmjenaartikla(root,upis());
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


