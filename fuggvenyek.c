#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fuggvenyek.h"
#include "debugmalloc.h"

//nehezseg alapjan kesziti el a tablat,
//tombben tarolja el az aknak koordinatajat, eslo koordinata a sor, masodik az oszlop


//GENERALAS
int** tabla_generalas(sor,oszlop,akna_db){

    int **matrix;
    matrix = (int*) calloc(sor, sizeof*matrix);


    //feltolti 0-val a megadott meretu tablat:
    srand(time(NULL));

    for(int i = 0; i<sor; i++){
        matrix[i] = calloc(oszlop, sizeof*(matrix[i]));
    }

    int i = 0;

    //aknak koordinata tombje, aknat -1 jelzi, az ures terulet pedig a calloc-cal letrehozott 0-k:

    while(i<akna_db){

        int r_sor = rand() % sor;                   //random sor, 1 ciklusig megorzi, hogy ellenorizni tudjuk, nincs e mar akna az adott helyen
        int r_oszlop = rand() % oszlop;             //random oszlop

        if (matrix[r_sor][r_oszlop] == 0){
            matrix[r_sor][r_oszlop] = -1;
            i++;
        }
    }

    return matrix;
}

//ez felfedi az aknakat es ures teruleteket, pl game over eseten, egyelore meg most tesztelesre hasznalva

void matrix_kiir(int **matrix, int sor, int oszlop){

    printf("\n\t");
//ez kiirja az oszlopok szamat, tippeles segitesehez
//if elagazasra a ketjegyu szamok miatt van szukseg, hogy ne csusszon el a kiiras, az egyjegyu szamok utan szokoz
    int i = 1;
    while(i <= oszlop){
        if(i<10){
            printf(" %d." , i);
            i++;
        }
        else{
            printf("%d." , i);
            i++;
        }
    }
    printf("\n\t");

    printf("\n\t");
    for(int k = 0; k<sor; k++){
        for(int l = 0;l<oszlop;l++){
            if(matrix[k][l] == 0)                   //ez az if azert van, mert a -1 es a 0 nem egyenlo szelesseguek, es elcsuszna a kiiras
                printf("[ ]", matrix[k][l]);      //ezert -1 helyett latvanyosabb es 1 egyseg hosszu "*" karaktert ir ki, 0 helyett ures dobozt
            else if(matrix[k][l] == -1)  //ha szeretnenk latni az aknakat, itt kell atirni -> bomba helyett csillag
                printf("[ ]", matrix[k][l]);
            else if(matrix[k][l] == -2)
                printf("[0]", matrix[k][l]);
            else                                    //egyeb esetben szomszedok szama
                printf("[%d]", matrix[k][l]);
        }
        printf("  %d.", k+1); //sorszam kiirasa, tippeles segitesere
        printf("%\n\t");

    }
}
//NYERTUNK-e

int nyeres_check(int **tabla, int sor, int oszlop){

    int hany_nulla_maradt = 0;

    for(int i =0; i<sor; i++){
        for(int j = 0; j<oszlop; j++){
            if(tabla[i][j] == 0)
                hany_nulla_maradt++;
            }
    }


    return hany_nulla_maradt;
}
//GAME_OVER
void game_over(int **tabla, int sor, int oszlop){

        printf("\n\n\n");
        printf("\t\t\tFELROBBANTOTTAD :( :( >:( \n\n\n\n");

    for(int k = 0; k<sor; k++){
        for(int l = 0;l<oszlop;l++){

            if(tabla[k][l] == -1)
                printf("[*]", tabla[k][l]);

            else
                printf("[ ]", tabla[k][l]);
        }
        printf("%\n");}
//free(tabla);
}

