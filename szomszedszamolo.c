#include <stdio.h>
#include "szomszedszamolo.h"
#include "debugmalloc.h"

//SZOMSZED SZOMSZED SZOMSZED SZOMSZED SZOMSZED


int szomszed_szamolo(int **tabla, int x, int y, int sor, int oszlop){

    if(tabla[x][y] == -1)
        ;

    else{

    int hany_szomszedja_akna = 0;

    if(x == 0 && y == oszlop){                //jobb felso sarok esete, ekkor a felette levo sor
            for(int i = -1; i<= 0; i++){                   //es a mellette levo oszlop nem letezik, arra ne menjen ellenorizni
                for(int j = -1; j<=0; j++){
                    if(i == 0 && j == 0)            //a jelenlegi cellat nem szabad beleszamolni, ebben az esetben ne csinaljon semmit
                        ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
                }
        }
    }
    else if(y == 0 && x == 0){                       //bal felso sarok esete
        for(int i = 0; i<=1; i++){
            for(int j = 0; j<=1; j++){
                if(i == 0 && j == 0)
                        ;
                else{
                    if(tabla[x+i][y+j] == -1)
                        hany_szomszedja_akna ++;
                }
            }
        }
    }
    else if ((x == 0) && (y>0) && (y<oszlop)){       //sima elso sor esete
            for(int i=0; i<=1; i++){
                for(int j = -1; j<=1; j++){
                    if(i == 0 && j == 0)
                        ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
                }
            }
        }
                                                                //sorbol ki kell vonni egyet, hiszen a dinamikusan letrehozott tombben a sornak is indexei vannak
    else if((x == sor-1) && (y>0) && (y<oszlop)){       //sima utolso sor esete, nem sarkok
            for(int i=-1; i<=0; i++){
                for(int j = -1; j<=1; j++){
                    if(i == 0 && j == 0)
                        ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
                }
            }
        }
    else if(x == sor-1 && y == 0){                     //bal also sarok:
            for(int i=-1; i<=0; i++){
                for(int j = 0; j<=1; j++){
                    if(i == 0 && j == 0)
                        ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
                }
            }
        }
    else if(x == sor-1 && y == oszlop){                //jobb also sarok esete
            for(int i=-1; i<=0; i++){
                for(int j = -1; j<=0; j++){
                    if(i == 0 && j == 0)
                    ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
                }

            }
    }
    else if((y == 0) && (x > 0) && (x < sor)){        //ha csak siman az elso oszlopban vagyunk, de nem sarokban
        for(int i = -1; i<=1; i++){
            for(int j = 0; j<=1; j++){
                if(i == 0 && j == 0)
                        ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
            }
        }

    }
    else if((y == oszlop) && (x > 0) && (x < sor)){   //ha csak siman az utolso oszlopban vagyunk, de nem sarokban
        for(int i = -1; i<=1; i++){
            for(int j = -1; j<=0; j++){
                if(i == 0 && j == 0)
                        ;
                    else{
                        if(tabla[x+i][y+j] == -1)
                            hany_szomszedja_akna ++;
                    }
            }
        }
    }
else{                                                    //ha pedig nem a szelso helyeken vagyunk, mind a 8 szomszedot nezzuk:
    for(int i=-1; i<=1; i++){
        for(int j = -1; j<=1; j++){
                if(i == 0 && j == 0)
                    ;
                else{
                    if(tabla[x+i][y+j] == -1)
                        hany_szomszedja_akna ++;
                }
        }
    }
}
if(hany_szomszedja_akna == 0)
   return -2; //mivel a 0-t mar elhasznaltuk a calloccal feltolteshez, azt nem irjuk ki, a mar felfedett ures teruletet -2-vel jeloljuk
else{
    return hany_szomszedja_akna;
}
}
}
//a folyamatos feltarasert felelos loop() fuggveny:





//LOOP





void loop(int **tabla, int x, int y, int sor, int oszlop){  //ha tablan kivul vagyunk, return

    if(x<0 || y<0 || x>=sor || y>=oszlop){
        return;}

    if(tabla[x][y] != 0 && tabla[x][y] != -2){          //ha a mezo nem 0 (mar neztuk) vagy nem feltart 0 azaz -2, akkor nem kell szamolni semmit
        return;
        }

    tabla[x][y] = szomszed_szamolo(tabla,x,y,sor,oszlop);       //minden egyeb esetben irja at a mezot a szomszedos aknak szamara, akkor is ha az 0, ekkor -2-re valtozik

// +1 +1                                                                        //mind a 8 iranyba megindulunk, de csak akkor folytatjuk, ha 0 vagy feltart 0 azaz -2 van a mezoben
    if(x+1>=0 && y+1>=0 && x+1<sor && y+1<oszlop){
        if(tabla[x+1][y+1] == 0 && szomszed_szamolo(tabla,x+1,y+1,sor,oszlop) == -2){
            loop(tabla,x+1,y+1,sor,oszlop);                         //rekurzio, ha a szomszed is 0, akkor nezze a szomszedot is, majd annak a szomszedjat... stb
        }
        else{
            tabla[x+1][y+1] = szomszed_szamolo(tabla,x+1,y+1,sor,oszlop); //egyeb esetben csak szamoljon, irja at, de ne menjen a szomszedokhoz
        }
    }

// 0 +1
    if(x>=0 && y+1>=0 && x<sor && y+1<oszlop){
        if(tabla[x][y+1] == 0 && szomszed_szamolo(tabla,x,y+1,sor,oszlop) == -2){
    loop(tabla,x,y+1,sor,oszlop);
        }
        else{
            tabla[x][y+1] = szomszed_szamolo(tabla,x,y+1,sor,oszlop);
        }
    }

// -1 +1
  if(x-1>=0 && y+1>=0 && x-1<sor && y+1<oszlop){
        if(tabla[x-1][y+1] == 0 && szomszed_szamolo(tabla,x-1,y+1,sor,oszlop) == -2){
            loop(tabla,x-1,y+1,sor,oszlop);
        }
        else{
            tabla[x-1][y+1] = szomszed_szamolo(tabla,x-1,y+1,sor,oszlop);
        }
    }

// -1 0
   if(x-1>=0 && y>=0 && x-1<sor && y<oszlop){
        if(tabla[x-1][y] == 0 && szomszed_szamolo(tabla,x-1,y,sor,oszlop) == -2){
            loop(tabla,x-1,y,sor,oszlop);
        }
        else{
            tabla[x-1][y] = szomszed_szamolo(tabla,x-1,y,sor,oszlop);
        }
    }
// -1 -1
   if(x-1>=0 && y-1>=0 && x-1<sor && y-1<oszlop){
        if(tabla[x-1][y-1] == 0 && szomszed_szamolo(tabla,x-1,y-1,sor,oszlop) == -2){
            loop(tabla,x-1,y-1,sor,oszlop);
        }
        else{
            tabla[x-1][y-1] = szomszed_szamolo(tabla,x-1,y-1,sor,oszlop);
        }
   }

// 0 -1
   if(x>=0 && y-1>=0 && x<sor && y-1<oszlop){
        if(tabla[x][y-1] == 0 && szomszed_szamolo(tabla,x,y-1,sor,oszlop) == -2){
            loop(tabla,x,y-1,sor,oszlop);
        }
        else{
            tabla[x][y-1] = szomszed_szamolo(tabla,x,y-1,sor,oszlop);
        }
}

// +1 -1
  if(x+1>=0 && y-1>=0 && x+1<sor && y-1<oszlop){
        if(tabla[x+1][y-1] == 0 && szomszed_szamolo(tabla,x+1,y-1,sor,oszlop) == -2){
            loop(tabla,x+1,y-1,sor,oszlop);
        }
        else{
            tabla[x+1][y-1] = szomszed_szamolo(tabla,x+1,y-1,sor,oszlop);
        }
  }

// +1 0
    if(x+1>=0 && y>=0 && x+1<sor && y<oszlop){
        if(tabla[x+1][y] == 0 && szomszed_szamolo(tabla,x+1,y,sor,oszlop) == -2)
            loop(tabla,x+1,y,sor,oszlop);
        else{
            tabla[x+1][y] = szomszed_szamolo(tabla,x+1,y,sor,oszlop);
        }
    }
}








