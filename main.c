#include <stdio.h>
#include <stdlib.h>
#include "fuggvenyek.h"
#include "szomszedszamolo.h"
#include "debugmalloc.h"

int main(){
    FILE *nehezseg_sor;
    FILE *nehezseg_oszlop;
    FILE *mentes;

    int olvas = 0;
    int sor, oszlop, akna_db = 0;

//-NEHEZSEGEK
    void konnyu(){
        sor = 8;
        oszlop = 8;
        akna_db = 10;
    }
     void kozepes(){
        sor = 16;
        oszlop = 16;
        akna_db=40;
    }
    void nehez(){
        sor = 30;
        oszlop = 16;
        akna_db = 99;
    }
    void egyeni(){
        printf("Add meg a sorok szamat:\t\t");
            scanf("%d", &sor);
        printf("\nAdd meg az oszlopok szamat:\t");
            scanf("%d", &oszlop);
        printf("\nAdd meg az aknak szamat:\t");
            scanf("%d", &akna_db);
            if(akna_db>sor*oszlop){
                printf("Ennyi aknat le se lehet tenni... Probald meg kevesebbel!:\t");
                scanf("%d", &akna_db);
            }
        }
        //a felhasznalo 1, 2 es 3 kozul kivalasztja a nehezseget.

        //printf("\nUdv, kedves Laborvezeto, remelhetoleg az egyetlen, akinek valaha is futtatnia kell ezt a szornyuseget! \nSajnalom, es kellemes 'jatekot'!");
        //printf("\n\n\tHogy  hamar vege legyen, az egyeni nehezseget ajanlom (4) 2x2 tablan 1 db aknaval.");
    int valasztott;
    printf("\n\n\n\t\tValassz nehezseget:\n\t\t\t [1]\t-konnyu\n \t\t\t [2]\t-kozepes\n\t\t\t [3]\t-nehez\n\t\t\t [4]\t-egyeni:\n\t\t\t [5]\t-fajlbol betolt: \t");
    scanf("%d", &valasztott);

    if(valasztott == 1)
        konnyu();

    else if(valasztott == 2)
        kozepes();

    else if(valasztott == 3){
        printf("\n\n\nBiztos?? Hat jo...\n\n\n");
        nehez();
    }

    else if(valasztott == 4){
            printf("\n\n\tJo dontes :)\n\n\t");
        egyeni();

    }

    else if(valasztott == 5)
        olvas = 1;

    else{ //ki ne menjen a tablarol:
        while((valasztott != 1) && (valasztott != 2) && (valasztott != 3) && (valasztott != 4) && (valasztott != 5)){
            printf("\n\n\n\t\tIlyen nehezseg nincs, (1-5):\t");
            scanf("%d", &valasztott);
            if(valasztott == 1)
                konnyu();

            else if(valasztott == 2)
                kozepes();

            else if(valasztott == 3)
                nehez();

            else if(valasztott == 4)
                egyeni();

            else if(valasztott == 5)
                olvas = 1;
        }
    }
    //TABLA GENERALASA, vagy beolvasasa
        int **tabla;

        if(valasztott != 5)
            tabla = tabla_generalas(sor,oszlop,akna_db);


        else{ //beolvassuk fajlbol

            nehezseg_sor = fopen("nehez_sor.txt", "r");
            if(nehezseg_sor == NULL){
                    printf("Sikertelen beolvasas, biztos letezik a fajl?\n");
                    return; }
                                                                                        //eloszor hogy hany soros
            fscanf(nehezseg_sor, "%d", &sor);
            //printf("(%d)",sor); teszt kiiras
            fclose(nehezseg_sor);


            nehezseg_oszlop = fopen("nehez_oszlop.txt", "r");
            if(nehezseg_oszlop == NULL){
                    printf("Sikertelen beolvasas, biztos letezik a fajl?\n");
                    return; }                                                               //aztan hogy hany oszlopos
            fscanf(nehezseg_oszlop, "%d", &oszlop);
            //printf("(%d)",oszlop); teszt kiiras
            fclose(nehezseg_oszlop);

            tabla = (int*) calloc(sor, sizeof*tabla);                                       //foglaljunk neki teruletet
            for(int i = 0; i<sor; i++)
                tabla[i] = calloc(oszlop, sizeof*(tabla[i]));

            for(int k = 0; k<sor; k++){
                for(int l = 0; l<oszlop; l++)
                    printf(tabla[k][l]);
            }

            mentes = fopen("save.txt", "r");            //majd az egesz tabla johet
                if(mentes == NULL){
                    printf("Nem sikerult betolteni :( Biztosan letezik a fajl?");
                return;
                }

            for(int i = 0; i<sor; i++){                 //tabla elhelyezese a 2d tombunkben
                for(int j = 0; j<oszlop; j++){
                    int c = fgetc(mentes);
                    //if(c=='\n')                        //ezt a sortorest kesobb kivettem, mert csak a baj van vele, egy sorba kerul minden es ugy olvassuk vissza
                        //j--;
                    if(c == '9')                       //kulonben dekodolni kell mert a szamokat karakterekkent mentette el a txt-ben
                        tabla[i][j] = -1;               //az aknak helyet 9-essel kodoltuk
                    else if(c == '0')
                        tabla[i][j] = 0;                //a feltart 0-kat azaz -2-eseket 'a' betuvel kodoltuk
                    else if(c == 'a')
                        tabla[i][j] = -2;
                    else if(c == '1')
                        tabla[i][j] = 1;
                    else if(c=='2')
                        tabla[i][j] = 2;
                    else if(c=='3')
                        tabla[i][j] = 3;
                    else if(c=='4')
                        tabla[i][j] = 4;
                    else if(c=='5')
                        tabla[i][j] = 5;
                    else if(c=='6')
                        tabla[i][j] = 6;
                    else if(c=='7')
                        tabla[i][j] = 7;
                    else if(c=='8')
                        tabla[i][j] = 8;
                }
            }
            fclose(mentes);
        }

    printf("\n\n\nA valasztott nehezseghez tartozo sorok szama:     %d\n\t oszlop szama: \t\t\t\t%d\n\t elhelyezett aknak szama: \t\t%d\n\n", sor, oszlop, akna_db);
    printf("A jatekallas fajlba mentesehez a sor koordinatajanak (-1)-et adj meg!\n\n\n");

    //teszt kiiras:
    matrix_kiir(tabla, sor, oszlop);

    //elso lepes elott informacio a jatekosnak:

    printf("\n\t\t\tKezdodjon a jatek! Koordinatankent kell tippelni.)");
    printf("\n\n\t\t\tEloszor a sor szamat, ami 1-tol a valaszott nehezseg sor darabszamaig terjed. \t");

    printf("\n\n\t\t\tMajd az oszlopot, szinten 1-tol az oszlop darabszamaig. Lasd feljebb\n\t");

    //tobbi lepes:
    int i = 0; //while ciklus megtoresere, ha vesztett vagy nyert
    int ment = 0;

     int *tipp;                                         //dinamikus tombben taroljuk a tippeket is, mindig ugyanabban a tombben
        tipp = (int*) malloc(2 * sizeof(int));

    while(i!=-1){
                               //ameddig nem lep aknara a jatekos, addig megy korbe korbe a tippeles
                 //kesobb nem fognak kelleni, a feltaras majd a matrixot modositja, kiirashoz pl 0 helyett -2 lesz a mar feltart tomb erteke
                                                            //egyeb esetben 1-8ig jeloli a szomszedokat
        printf("\n\t\tSor : \t\t");
        scanf("%d", &tipp[0]);
            while(tipp[0]>sor || tipp[0]<-1){                         //nagyobb/kisebb szamot ne engedjen megadni
                printf("Ne menj ki a tablarol! Max sor = %d \n Sor:\t",sor);
                scanf("%d", &tipp[0]);
                scanf("%d", &tipp[1]);
                if(tipp[0] == -1)
                    ment = 1;

            }
            tipp[0] -= 1;           //kivonunk egyet az indexeles miatt, mivel a szamozas 1-tol kezd, de az index 0-tol

            //ez oldja meg a fajlba mentest, ket kulon fajl, nehez.txt-ben a nehezseg, save-ben a tabla
            if(tipp[0] == -2 || ment == 1){

                mentes = fopen("save.txt", "w");
                if(mentes == NULL){
                    printf("Sikertelen mentes\n");
                    return;
                }
                for(int i = 0; i<sor; i++){
                    for(int j = 0; j<oszlop; j++){
                        if(tabla[i][j] == -1)
                            fprintf(mentes, "9"); //itt -1 helyett 9-et rakunk a beolvasas miatt
                        else if(tabla[i][j] == -2)
                            fprintf(mentes,"a"); //itt pedig a betut
                        else
                            fprintf(mentes,"%d",tabla[i][j]); //egyebkent a szomszedok szama megy 0-8ig
                    }
                    //fprintf(mentes, "\n"); //ezt a sortorest kesobb kivettem, mert csak a baj van vele, egy sorba kerul minden es ugy olvassuk vissza
                }
            fclose(mentes);

//kulon fajlban lesz a nehezseg sorszama

            nehezseg_sor = fopen("nehez_sor.txt", "w");
            if(nehezseg_sor == NULL){
                printf("Sikertelen mentes\n");
                    return;
            }
            fprintf(nehezseg_sor,"%d",sor);
            fclose(nehezseg_sor);

//egy masikban pedig a nehezseg oszlopszama
            nehezseg_oszlop = fopen("nehez_oszlop.txt", "w");
            if(nehezseg_oszlop == NULL){
                printf("Sikertelen mentes\n");
                    return;
            }
            fprintf(nehezseg_oszlop,"%d",oszlop);
            fclose(nehezseg_oszlop);

            printf("Sikeresen mentetted a jatekallast, a programmal azonos mappaban talalod a save.txt nevu fajlt.\n\n\nKesobb folytathatod!");
            for(int i = 0; i<sor; i++)             //mentes eseten tabla es tipp felszabaditasa, mar nincs ra szukseg, vissza fogjuk olvasni legkozelebb
                free(tabla[i]);
            free(tabla);
            free(tipp);
            break;
        }

//ha nem mentjuk, akkor folytatjuk a tippelest
        else{
        printf("\n\t\tOszlop : \t");
        scanf("%d", &tipp[1]);
            while(tipp[1]>oszlop || tipp[1]<0){
                printf("Ne menj ki a tablarol! Max oszlop = %d \n Oszlop:\t",oszlop);
                scanf("%d", &tipp[1]);
            }

            tipp[1] -= 1;

        if(tabla[tipp[0]][tipp[1]] == -1){
            game_over(tabla, sor, oszlop);
            free(tipp);
            for(int i = 0; i<sor; i++)             //game over eseten tabla es tipp felszabaditasa
                free(tabla[i]);
            free(tabla);
            i=-1;
            break;
                    //megtorjuk a while ciklust

        }
        else{

        int x = tipp[0];            //elnevezzuk x-nek es y-nak, hogy konnyebb legyen atadni a fuggvenyeknek, igy is eleg hosszuak es sok felteteles elagazasuk van
        int y = tipp[1];

        loop(tabla, x, y, sor, oszlop);
        matrix_kiir(tabla, sor, oszlop);         //minden lepesnel kiirjuk

        if(nyeres_check(tabla,sor,oszlop) == 0){

            printf("\n\n\n\t\t\t\t :) :) :) :) :) :) :) :) GRATULALOK, NYERTEL! :) :) :) :) :) :) :) :) :) :) :)");
            free(tipp);
            for(int i = 0; i<sor; i++)             //game over eseten tabla es tipp felszabaditasa
                free(tabla[i]);
            free(tabla);
            i=-1;
            break;
        }

        tipp[0] = 0;                 //nem felszabaditjuk itt meg, jon a kovetkezo tipp, csak lenullazzuk, hiszen mindig hozzaadja a tippet
        tipp[1] = 0;

        i++;

        }
        }
    }

//debugmalloc_log_file("memlog.txt"); //ha a debugot inkabb fajlba szeretnenk
    return 0;
}
