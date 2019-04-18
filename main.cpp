//
//  main.cpp
//  Amoba
//
//  Created by Tóth Gergő on 2019. 04. 03..
//  Copyright © 2019. Tóth Gergő. All rights reserved.
//
//  --Készítette: Tóth Gergő, Mérnökinformatika - SZE
//  --Neptun kód: IRIE5X
//  --Email cím: tgery3@gmail.com
//
//Kérdések: negatív, vagy pedig végtelen pálya pozitívban?

#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;



int main() {
    int index = 5;
    int playersorszam = 1;
    float jatekvege = 0;
    
    
    vector<vector <int>> tabla;
    tabla.reserve(100);
    tabla.resize(index);
    for (int i = 0; i < index; ++i)
        tabla[i].resize(index);

    
    //Táblacache
    vector<vector <int>> tablacache;
    tablacache.resize(index);
    for (int i = 0; i < index; ++i)
        tablacache[i].resize(index);
    
    //A tabla tomb nullazasa:
    for(int i=0; i<=4; i++){
        for(int a=0; a<=4; a++){
            tabla[i][a] = 0;
        }
    }
    
    
    do{
        //A bekért változókra NULL azaz semmivel töltjük fel, mivel a 0 egy érték már!
        int bekertsor1 = NULL;
        int bekertoszlop1 = NULL;
        int bekertsor2 = NULL;
        int bekertoszlop2 = NULL;
        int bekertoszlop1n = NULL;
        int bekertsor1n = NULL;
        int bekertoszlop2n = NULL;
        int bekertsor2n = NULL;
        long pos1=0;
        long pos2=0;
        bool pos1ures = true;
        bool pos2ures = true;
        
        
        //Bekérés a 1. játékosoktól
        if(playersorszam == 1){
            //Pálya mutatása:
            //Addig megy, amíg nem tölt ki valamit, ergó nem 0, hanem valami más..
             do{

                 
                cout << "1. játékos (X) \nAdja meg az oszlopot: ";
                cin >> bekertoszlop1;
                cout << "Adja meg a sort:";
                cin >> bekertsor1;
                 //Hogy ne 0-tól induljon a kimutatás
                 bekertsor1-=1;
                 bekertoszlop1-=1;
                 
                 //Ha esetleg nagyobb lenne a szám
                 int maxindex = 0;
                 
                 //Csak akkor resizeolódik a tábla, ha pozitív értékbe adunk meg 5-nél vagy az indexnél nagyobb értéket.
                 if(bekertsor1n >= 0 && bekertoszlop1n >= 0){
                     if(bekertsor1 >= bekertoszlop1){
                         maxindex = bekertsor1;
                     }
                     if(bekertoszlop1 >= bekertsor1){
                         maxindex = bekertoszlop1;
                     }
                 }
                 
                 //Ha a bekért szám nagyobb az indexnél, akkor növelni fogja a vektor méretét
                 if(maxindex >= index){
                     
                     tabla.resize(maxindex+1);
                     for (int i = 0; i < maxindex+1; ++i)
                         tabla[i].resize(maxindex+1);
                     index = maxindex;
                 }

                 
                 
                 
                 //Mínusz abszolútértékre váltás
                 if(bekertsor1 < 0){
                     //Elmentjük a negatív értéket egy változóba, később jó lesz:)
                     bekertsor1n = (bekertsor1)+1;
                     bekertsor1 = abs(bekertsor1)-1;
                     
                     //Ha csak -1 a bekért érték, akkor elég csak egyszer insertelni.
                     //Hozzáadunk annyi nullát a függőleges sorba, amennyi minusz értéket kapott.
                     //Ezután a hozzáadott sor(ok)hoz feltöltjük a vízszintes sort is nullásokkal, annyival, amekkora a tábla[sor] értéke alapból
                     if(bekertsor1 == 1){
                         tabla.emplace(tabla.begin(), 0);
                         for(int j = 0; j<tabla[index-1].size(); j++){
                             tabla[0].insert(std::begin(tabla[0]), 0);
                         }
                     }
                     
                     if(bekertsor1 > 1){
                         bekertsor1 -= 1;
                         for(int i=0; i<bekertsor1; i++){
                             tabla.emplace(tabla.begin(), 0);
                         }
                         for(int a=0; a<bekertsor1; a++){
                             for(int j = 0; j<tabla[j+bekertsor1].size(); j++){
                                 tabla[a].push_back(0);
                             }
                         }
                         
                     }
                     
                     
                 }
                 
                 if(bekertoszlop1 < 0){
                     bekertoszlop1n = (bekertoszlop1)+1;
                     bekertoszlop1 = abs(bekertoszlop1)-1;
                     
                     //Minden függőleges sor elé rakunk táblaméretnyi nullást
                     //Így produkálva egy új függőleges sort.
                     if(bekertoszlop1 == 1){
                         for(int i=0; i<tabla.size(); i++){
                             tabla[i].insert(std::begin(tabla[i]), 0);
                         }
                     }else{
                         for(int a = 0; a<bekertoszlop1; a++){
                             for(int i=0; i<tabla.size(); i++){
                                 tabla[i].insert(std::begin(tabla[i]), 0);
                             }
                         }
                     }
                     
                                          
                 }
                 
                 
                 //cout << "ABSsor: " << bekertsor1 << "\n";
                 //cout << "ABSoszlop: " << bekertoszlop1 << "\n";
                 
                
                 //Ha a bekértoszlop negatív, akkor igazából a bekértoszlop 0 lesz
                 if(bekertoszlop1n < 0){
                     bekertoszlop1 = 0;
                 }
                 if(bekertsor1n == -1){
                     bekertsor1 = 0;
                 }
                 
                 if(tabla[bekertsor1][bekertoszlop1] != 0){
                     cout << "Bekért: " << bekertsor1 << "," << bekertoszlop1 << "\n";
                     cout << "Ezen a pozicion szerepel mar egy jel. Valassz masikat! \n";
                     
                     //Pálya mutatása, és behelyettesítése karakterrel:
                     for(int x=0; x<=tabla.size()-1; x++){
                         cout << x+1 << ".\t";
                         for(int y=0; y<=tabla[x].size()-1; y++){
                             if(tabla[x][y] == 0){cout << "-";}
                             if(tabla[x][y] == 1){cout << "EZ";}
                             if(tabla[x][y] == 2){cout << "O";}
                         }
                         cout << "\n";
                     }
                 }
                 
                 
                 if(tabla[bekertsor1][bekertoszlop1] == 0){
                     //cout << "Bekért: " << bekertsor1n << "," << bekertoszlop1n << "\n";
                     if(bekertsor1n < 0 && bekertoszlop1n >= 0){
                        tabla[0][bekertoszlop1] = 1;
                     }
                     if(bekertoszlop1n < 0 && bekertsor1n >= 0){
                         tabla[bekertsor1][0] = 1;
                     }
                     if(bekertoszlop1n >= 0 && bekertsor1n >= 0){
                         tabla[bekertsor1][bekertoszlop1] = 1;
                     }
                     if(bekertoszlop1n < 0 && bekertsor1n < 0){
                         tabla[0][0] = 1;
                     }
                         //Pálya mutatása, és behelyettesítése karakterrel:
                         for(int x=0; x<=tabla.size()-1; x++){
                             cout << x+1 << ".\t";
                             for(int y=0; y<=tabla[x].size()-1; y++){
                                 if(tabla[x][y] == 0){cout << "-";}
                                 if(tabla[x][y] == 1){cout << "X";}
                                 if(tabla[x][y] == 2){cout << "O";}
                             }
                             cout << "\n";
                         }
                     
                     }
             }while (tabla[bekertsor1][bekertoszlop1] == 0
                     && tabla[bekertsor1][0] == 0
                     && tabla[0][bekertoszlop1] == 0);
            
            //Elbírálás
            double pontszam = 0;
            for(int x=0; x<=tabla.size()-1; x++){
                for(int y=0; y<=tabla[x].size()-1; y++){
                    //Ha vízszintesen összejön az 5 db, akkor a pontszám +=1
                    //Majd a playersorszám nullázódik, és a játékvége = 1, tehát vége a játékciklusnak
                    if(tabla[x][y] == 1){
                        pontszam +=1;
                        if(pontszam >= 5){
                            cout << "Nyert az 1. játékos! Szép munka :) \n";
                            playersorszam = 0;
                            jatekvege = 1;
                        }
                    }else{
                        pontszam = 0;
                    }
                }
            }
            
            for(int x=0; x<=tabla.size()-1; x++){
                for(int y=0; y<=tabla.size()-1; y++){
                    //Ha függőlegesen összejön az 5 db, akkor a pontszám +=1
                    if(tabla[y][x] == 1){
                        pontszam +=1;
                        if(pontszam >= 5){
                            cout << "Nyert az 1. játékos! Szép munka :) \n";
                            playersorszam = 0;
                            jatekvege = 1;
                        }
                    }else{
                        pontszam = 0;
                    }
                }
            }
            
            
            //Indexkeresés a vektorban, majd balról-jobbra keresés (fentről le - lentről fel)
            for(int a = 0; a<tabla.size(); a++){
                for(int i =0; i<tabla[0].size(); i++) {
                    if(tabla[a][i] == 1){
                        if(pos1ures == false){
                            pontszam = 0;
                        }
                        pos1 = i;
                        pos1ures = false;
                        
                        
                        for(int j=0; j<=tabla[0].size(); j++){
                            if((j+pos1) < tabla[0].size()-1){
                                if(tabla[(j+pos1)][(j+pos1)] == 1) {
                                    pontszam +=1;
                                    if(pontszam == 5){
                                        cout << "Nyert az 1. játékos! Szép munka :) \n";
                                        playersorszam = 0;
                                        jatekvege = 1;
                                    }
                                }else{
                                    pontszam = 0;
                                }
                            }
                        }
                    }
                }
            }
            //Indexkeresés a vektorban, majd jobbról-balra keresés (fentről le - lentről fel)
            for(int a = 0; a<tabla.size(); a++){
                for(int i =0; i<tabla[0].size(); i++) {
                    if(tabla[a][i] == 1){
                        if(pos1ures == false){
                            pontszam = 0;
                        }
                        pos1 = i;
                        pos1ures = false;
                        
                        for(int j=0; j<=tabla[0].size(); j++){
                            if((pos1-j) < tabla[0].size()){
                                if(tabla[j][(pos1-j)] == 1) {
                                    pontszam +=1;
                                    if(pontszam == 5){
                                        cout << "Nyert az 1. játékos! Szép munka :) \n";
                                        playersorszam = 0;
                                        jatekvege = 1;
                                    }
                                }else{
                                    pontszam = 0;
                                }
                            }
                        }
                    }
                }
            }
            
            
            //Játékosváltás, ha nincs még vége a játéknak
            if(jatekvege == 1){
                playersorszam = 0;
            }else{
                playersorszam = 2;
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        //Bekérés a 2. játékosoktól
        if(playersorszam == 2){
            //Pálya mutatása:
             do{
                cout << "2. játékos (O) \nAdja meg az oszlopot: ";
                cin >> bekertoszlop2;
                cout << "Adja meg a sort:";
                cin >> bekertsor2;
                 bekertsor2-=1;
                 bekertoszlop2-=1;

                 
                 int maxindex = 0;
                 if(bekertsor2n >= 0 && bekertoszlop2n >= 0){
                     if(bekertsor2 >= bekertoszlop2){
                         maxindex = bekertsor2;
                     }
                     if(bekertoszlop2 >= bekertsor2){
                         maxindex = bekertoszlop2;
                     }
                 }
                 
                 if(maxindex >= index){
                     
                     tabla.resize(maxindex+1);
                     for (int i = 0; i < maxindex+1; ++i)
                         tabla[i].resize(maxindex+1);
                     index = maxindex;
                 }

                 
                 
                 
                 //Mínusz abszolútértékre váltás
                 if(bekertsor2 < 0){
                     //Elmentjük a negatív értéket egy változóba, később jó lesz:)
                     bekertsor2n = bekertsor2+1;
                     bekertsor2 = abs(bekertsor2)-1;
                     
                     //Ha csak -1 a bekért érték, akkor elég csak egyszer insertelni.
                     //Hozzáadunk annyi nullát a függőleges sorba, amennyi minusz értéket kapott.
                     //Ezután a hozzáadott sor(ok)hoz feltöltjük a vízszintes sort is nullásokkal, annyival, amekkora a tábla[sor] értéke alapból
                     if(bekertsor2 == 1){
                         tabla.emplace(tabla.begin(), 0);
                         for(int j = 0; j<tabla[index-1].size(); j++){
                             tabla[0].insert(std::begin(tabla[0]), 0);
                         }
                     }
                     
                     if(bekertsor2 > 1){
                         bekertsor2 -=1;
                         for(int i=0; i<bekertsor2; i++){
                             tabla.emplace(tabla.begin(), 0);
                         }
                         for(int a=0; a<bekertsor2; a++){
                             for(int j = 0; j<tabla[j+bekertsor2].size(); j++){
                                 tabla[a].push_back(0);
                             }
                         }
                         
                     }
                     
                     
                 }
                 
                 if(bekertoszlop2 < 0){
                     bekertoszlop2n = (bekertoszlop2)+1;
                     bekertoszlop2 = abs(bekertoszlop2)-1;
                     
                     //Minden függőleges sor elé rakunk táblaméretnyi nullást
                     //Így produkálva egy új függőleges sort.
                     if(bekertoszlop2 == 1){
                         for(int i=0; i<tabla.size(); i++){
                             tabla[i].insert(std::begin(tabla[i]), 0);
                         }
                     }else{
                         for(int a = 0; a<bekertoszlop2; a++){
                             for(int i=0; i<tabla.size(); i++){
                                 tabla[i].insert(std::begin(tabla[i]), 0);
                             }
                         }
                     }
                     
                     
                 }
                
                 if(bekertoszlop2n < 0){
                     bekertoszlop2 = 0;
                 }
                 if(bekertsor2n == -1){
                     bekertsor2 = 0;
                 }
                 
                     if(tabla[bekertsor2][bekertoszlop2] != 0){
                         cout << "Bekért: " << bekertsor1 << "," << bekertoszlop1 << "\n";
                         cout << "Ezen a pozicion szerepel mar egy jel. Valassz masikat! \n";
                     }
                     if(tabla[bekertsor2][bekertoszlop2] == 0){
                         //cout << "Bekért: " << bekertsor1 << "," << bekertoszlop1 << "\n";
                         if(bekertsor2n < 0 && bekertoszlop2n >= 0){
                             tabla[0][bekertoszlop2] = 2;
                         }
                         if(bekertoszlop2n < 0 && bekertsor2n >= 0){
                             tabla[bekertsor2][0] = 2;
                         }
                         if(bekertoszlop2n >= 0 && bekertsor2n >= 0){
                             tabla[bekertsor2][bekertoszlop2] = 2;
                         }
                         if(bekertoszlop2n < 0 && bekertsor2n < 0){
                             tabla[0][0] = 2;
                         }
                         
                         //Pálya mutatása, és behelyettesítése karakterrel:
                         for(int x=0; x<=tabla.size()-1; x++){
                             cout << x+1 << ".\t";
                             for(int y=0; y<=tabla[x].size()-1; y++){
                                 if(tabla[x][y] == 0){cout << "-";}
                                 if(tabla[x][y] == 1){cout << "X";}
                                 if(tabla[x][y] == 2){cout << "O";}
                             }
                             cout << "\n";
                         }
                         
                     }
            }while (tabla[bekertsor2][bekertoszlop2] == 0
                    && tabla[bekertsor2][0] == 0
                    && tabla[0][bekertoszlop2] == 0);
            
            
            //Elbírálás
            double pontszam = 0;
            for(int x=0; x<=tabla.size()-1; x++){
                for(int y=0; y<=tabla.size()-1; y++){
                    //Ha vízszintesen összejön az 5 db, akkor a pontszám +=1
                    //Majd a playersorszám nullázódik, és a játékvége = 1, tehát vége a játékciklusnak
                    if(tabla[y][x] == 2){
                        pontszam +=1;
                        if(pontszam >= 5){
                            cout << "Nyert a 2. játékos! Szép munka :) \n";
                            playersorszam = 0;
                            jatekvege = 1;
                        }
                    }else{
                        pontszam = 0;
                    }
                }
            }
            
            for(int x=0; x<=tabla.size()-1; x++){
                for(int y=0; y<=tabla.size()-1; y++){
                    //Ha függőlegesen összejön az 5 db, akkor a pontszám +=1
                    if(tabla[x][y] == 2){
                        pontszam +=1;
                        if(pontszam >= 5){
                            cout << "Nyert a 2. játékos! Szép munka :) \n";
                            playersorszam = 0;
                            jatekvege = 1;
                        }
                    }else{
                        pontszam = 0;
                    }
                }
            }
            
            //Indexkeresés a vektorban, majd balról-jobbra keresés (fentről le - lentről fel)
            for(int a = 0; a<tabla.size(); a++){
                for(int i =0; i<tabla[0].size(); i++) {
                    if(tabla[a][i] == 2){
                        if(pos2ures == false){
                            pontszam = 0;
                        }
                        pos2 = i;
                        pos2ures = false;
                        
                        
                        for(int j=0; j<=tabla[0].size(); j++){
                            if((j+pos2) < tabla[0].size()-1){
                                if(tabla[(j+pos2)][(j+pos2)] == 2) {
                                    pontszam +=1;
                                    if(pontszam == 5){
                                        cout << "Nyert a 2. játékos! Szép munka :) \n";
                                        playersorszam = 0;
                                        jatekvege = 1;
                                        tabla[3333][1] = 1;
                                    }
                                }else{
                                    pontszam = 0;
                                }
                            }
                        }
                    }
                }
            }
            for(int a = 0; a<tabla.size(); a++){
                for(int i =0; i<tabla[0].size(); i++) {
                    if(tabla[a][i] == 2){
                        if(pos2ures == false){
                            pontszam = 0;
                        }
                        pos2 = i;
                        pos2ures = false;

                        for(int j=0; j<=tabla[0].size(); j++){
                            if((pos2-j) < tabla[0].size()){
                                if(tabla[j][(pos2-j)] == 2) {
                                    pontszam +=1;
                                    if(pontszam == 5){
                                        cout << "Nyert a 2. játékos! Szép munka :) \n";
                                        playersorszam = 0;
                                        jatekvege = 1;
                                        tabla[3333][1] = 1;
                                    }
                                }else{
                                    pontszam = 0;
                                }
                            }
                        }
                    }
                }
            }
            
            
            
            //Játékosváltás, ha nincs még vége a játéknak
            if(jatekvege == 1){
                playersorszam = 0;
            }else{
                playersorszam = 1;
            }

        }
        
        
    }while(jatekvege != 1);
    
    
    
}
