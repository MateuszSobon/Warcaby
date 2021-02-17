#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include <math.h>

#define CZARNE 1
#define BIALE 0


struct lista 
{
    int p_x,p_y;
    int x,y;
    int a;

};

struct lista najnajlepsza;

struct elementlisty
{
    struct lista bicie;
    struct elementlisty* nast;
};

struct plansza 
{
    char plansza[8][8];
    int tura,zb1,zb2;
};

void wypisz(struct plansza plansza) // funkcja do wypisywania szachownicy 
{
    
    for(int i=0; i<8; i++)
     { 
        printf("  +---+---+---+---+---+---+---+---+ \n");
        printf("%d ", i);
        for (int  j=0; j<8; j++)
        {
            printf("| %c ",plansza.plansza[i][j]);
        }
         printf("| \n");
     }
     printf("  +---+---+---+---+---+---+---+---+ \n");
     printf("    0   1   2   3   4   5   6   7   \n");
     printf("Zbicia gracza 1: %d\nZbicia gracza 2: %d\nTura: %d: ",plansza.zb1,plansza.zb2,plansza.tura);
     printf("\n");
};

struct plansza pusta(void)  // inicjuje pustą plansze 
{
    struct plansza plansza; 
    
    for(int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            plansza.plansza[i][j]=' ';
        }
    }
    plansza.tura=1;
    return plansza;
};

struct plansza przypisz(void) // wpisuje w plansze figury TYLKO na początek gry!
{
    struct plansza plansza;
    int i=0;
    while (i<8)
    {
    plansza.plansza[0][i+1]='P';
    plansza.plansza[0][i]=' ';

    plansza.plansza[1][i]='P';
    plansza.plansza[1][i+1]=' ';

    plansza.plansza[2][i+1]='P';
    plansza.plansza[2][i]=' ';

    plansza.plansza[3][i]=' ';
    plansza.plansza[3][i+1]=' ';

    plansza.plansza[4][i]=' ';
    plansza.plansza[4][i+1]=' ';

    plansza.plansza[5][i]='p';
    plansza.plansza[5][i+1]=' ';

    plansza.plansza[6][i+1]='p';
    plansza.plansza[6][i]=' ';

    plansza.plansza[7][i]='p';  
    plansza.plansza[7][i+1]=' ';  

    i=i+2;
    };
    
    plansza.tura=1;
    plansza.zb1=0;
    plansza.zb2=0;

   return plansza;
};

int ocena(struct plansza plansza) //ocenia aktualny stan gry, kto wygrywa
{
    int liczba_bialych=0, liczba_czarnych=0;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if (plansza.plansza[i][j]=='P')
            liczba_bialych++;
            else if (plansza.plansza[i][j]=='Q')
            liczba_bialych+=2;
        }
    }

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if (plansza.plansza[i][j]=='p')
            liczba_czarnych++;
            else if (plansza.plansza[i][j]=='q')
            liczba_czarnych+=2;
        }
    }

    if (liczba_bialych==0 || liczba_czarnych==0)
    {
         return 100;  
    }
    else if (plansza.tura == 1)
    {
        return (liczba_bialych-liczba_czarnych);  
    }
    else
    {
        return (liczba_czarnych-liczba_bialych);
    }
    
    
};

struct elementlisty* dodaj_element(struct elementlisty* glowa, struct lista l) // dodaje element do listy ruchów
{
    struct elementlisty* ptr=calloc(1, sizeof(struct elementlisty));
    ptr->bicie=l;
    ptr->nast=NULL;

    if(glowa)
    {
        while(glowa->nast)
        {
            glowa=glowa->nast;
        }
        glowa->nast=ptr;
    }
    return ptr;
};

void wypisz_liste(struct elementlisty* glowa) //wypisuje liste ruchów POMOCNICZA FUNKCJA
{
    while (glowa)
    {
        printf("%d %d %d %d %d \n", glowa->bicie.p_x,glowa->bicie.p_y,glowa->bicie.x,glowa->bicie.y,glowa->bicie.a );
        glowa=glowa->nast;
    }
    printf("\n");
};

struct elementlisty* ruchy(struct plansza plansza) //funkcja tworzy liste możliwych ruchów dla gracza
{
    struct lista po_cos = {10, 10, 10, 10, 10}; //zeby bylo do czego sie odwolac
    struct elementlisty* glowa = dodaj_element(NULL, po_cos);

    for(int i = 0; i < 8; i++) // szukamy mozliwosci ruchu bez zbicicia
    {
        for(int j = 0; j < 8;j++)
        {
            if(plansza.tura == 0) // ruch dla bialych bez bicia
            {   
                if (plansza.plansza[i][j] == 'Q') // biale miejsca dla damki białej
                {
                    for(int w = i-1, k = j-1;w >= 0 && k >= 0;w--,k--) //ruchy bez bicia dla damki 1 przekatna do dolu
                    {
                        if(plansza.plansza[w][k]==' ')
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);   
                            // Dodaj do listy pkt i j k w 0
                        }
                        else break;  
                    }
                    for(int w = i+1, k = j+1;w < 8 && k < 8;w++,k++) //ruchy bez bicia dla damki 1 przekatna do góry
                    {
                        if(plansza.plansza[w][k]==' ')
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);
                            //Dodaj do listy pkt i j k w 0
                        }
                        else break;
                    }
                    for(int w = i+1, k = j-1;w < 8 && k >= 0;w++,k--) //ruchy bez bicia dla damki po 2 przekątnej w górę
                    {
                        if(plansza.plansza[w][k]==' ')
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);
                            // Dodaj do listy pkt i j k w 0
                        }
                        else break;
                    }   
                    for(int w = i-1, k = j+1;w >= 0 && k < 8;w--,k++) //ruchy bez bicia dla damki po 2 przekątnej w dół
                    {
                        if(plansza.plansza[w][k]==' ') 
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);
                            // Dodaj do listy pkt i j k w 0
                        }
                        else break;       
                    }
                }

                if (plansza.plansza[i][j]=='P') //szukamy wolnych miejsca dla pionkow bialych
                {                 
                    if (i+1<8 && j+1<8)
                    {
                        if (plansza.plansza[i+1][j+1]==' ') 
                        {
                            struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = i+1;
                                ruchy.y = j+1;
                                ruchy.a = 0;
                                dodaj_element(glowa,ruchy); //dodaj do listy pkt i j i+1 j+1 0
                        }
                    }                 
                    if (i+1<8 && j-1>=0)                 
                    {                    
                        if (plansza.plansza[i+1][j-1]==' ') 
                        {
                            struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = i+1;
                                ruchy.y = j-1;
                                ruchy.a = 0;
                                dodaj_element(glowa,ruchy);
                                //dodaj do listy pkt i j i+1 j-1 0 
                        } 
                    }                 
 
                }
            } 
            else if(plansza.tura == 1)  //ruch dla czarnych bez bicia 
            {
                if (plansza.plansza[i][j] == 'q') // wolne miejsca dla damki czarnej
                {
                    for(int w = i-1, k = j-1;w >= 0 && k >= 0;w--,k--) //ruchy bez bicia dla damki 1 przekatna do dolu
                    {
                        if(plansza.plansza[w][k]==' ')
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);   
                            // Dodaj do listy pkt i j k w 0
                        }
                        else break;  
                    }
                    for(int w = i+1, k = j+1;w < 8 && k < 8;w++,k++) //ruchy bez bicia dla damki 1 przekatna do góry
                    {
                        if(plansza.plansza[w][k]==' ')
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);
                            //Dodaj do listy pkt i j k w 0
                        }
                        else break;
                    }
                    for(int w = i+1, k = j-1;w < 8 && k >= 0;w++,k--) //ruchy bez bicia dla damki po 2 przekątnej w górę
                    {
                        if(plansza.plansza[w][k]==' ')
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);
                            // Dodaj do listy pkt i j k w 0
                        }
                        else break;
                    }   
                    for(int w = i-1, k = j+1;w >= 0 && k < 8;w--,k++) //ruchy bez bicia dla damki po 2 przekątnej w dół
                    {
                        if(plansza.plansza[w][k]==' ') 
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = w;
                            ruchy.y = k;
                            ruchy.a = 0;
                            dodaj_element(glowa,ruchy);
                            // Dodaj do listy pkt i j k w 0
                        }
                        else break;       
                    }
                }

                if (plansza.plansza[i][j]=='p')
                {                
                    if (i-1>=0 && j+1<8)                 
                    {                     
                        if (plansza.plansza[i-1][j+1]==' ') 
                        { 
                            struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = i-1;
                                ruchy.y = j+1;
                                ruchy.a = 0;
                                dodaj_element(glowa,ruchy);
                                //dodaj do listy pkt i j i-1 j+1 0
                        } 
                    }                 
                    if (i-1>=0 && j-1>=0)                 
                    {                     
                        if (plansza.plansza[i-1][j-1]==' ') 
                        {
                            struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = i-1;
                                ruchy.y = j-1;
                                ruchy.a = 0;
                                dodaj_element(glowa,ruchy);
                                 //dodaj do listy pkt i j i-1 j-1 0
                        } 
                    }   
                }               
            }                        
        

        }
    }
    for(int i = 0; i < 8;i++) //ruchy z biciem sa szukane
    {
        for(int j = 0; j < 8;j++)
        {
            if(plansza.tura == 0)//ruch z biciem dla bialych
            {
                if (plansza.plansza[i][j] == 'Q') // biale miejsca dla damki białej
                {
                    for(int w = i-1, k = j-1;w >= 0 && k >= 0;w--,k--) //ruchy z biciem dla damki 1 przekatna do dolu
                    {
                        if(w-1>=0 && k-1>=0)
                        {
                            if(plansza.plansza[w-1][k-1] == ' ' && (plansza.plansza[w][k]=='q' || plansza.plansza[w][k]=='p'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w-1;
                                ruchy.y = k-1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                        
                    }
                    for(int w=i+1, k=j+1; w<8 && k<8; w++,k++) //ruchy z biciem dla damki 1 przekatna do góry
                    {
                        if(w+1<8 && k+1<8)
                        {
                            if(plansza.plansza[w+1][k+1] == ' ' && (plansza.plansza[w][k]=='q' || plansza.plansza[w][k]=='p'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w+1;
                                ruchy.y = k+1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                    }
                    for(int w = i+1, k = j-1; w<8 && k>=0; w++,k--) //ruchy z biciem dla damki po 2 przekątnej w górę
                    {
                        if(w+1<8 && k-1>=0)
                        {
                            if(plansza.plansza[w+1][k-1] == ' ' && (plansza.plansza[w][k]=='q' || plansza.plansza[w][k]=='p'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w+1;
                                ruchy.y = k-1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                    }   
                    for(int w = i-1, k = j+1;w >= 0 && k < 8;w--,k++) //ruchy z bicia dla damki po 2 przekątnej w dół
                    {
                        if(w-1>=0 && k+1<8)
                        {
                            if(plansza.plansza[w-1][k+1] == ' ' && (plansza.plansza[w][k]=='q' || plansza.plansza[w][k]=='p'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w-1;
                                ruchy.y = k+1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                    }
                }

                if (plansza.plansza[i][j]=='P')
                {
                    if ((i+2<8 && j+2<8)) //sprawdzamy czy nie wychodza poza plansze
                    {
                        if ((plansza.plansza[i+1][j+1]=='p' || plansza.plansza[i+1][j+1]=='q') && (plansza.plansza[i+2][j+2] == ' ')) 
                        {   
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = i+2;
                            ruchy.y = j+2;
                            ruchy.a = 1;
                            dodaj_element(glowa,ruchy);
                            /*dodaj do listy pkt i j i+1 j+1 1*/
                        }
                    }                 
                    if (i+2<8 && j-2>=0)                
                    {                    
                        if ((plansza.plansza[i+1][j-1]=='p' || plansza.plansza[i+1][j-1]=='q') && (plansza.plansza[i+2][j-2] == ' ')) 
                        {   
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = i+2;
                            ruchy.y = j-2;
                            ruchy.a = 1;
                            dodaj_element(glowa,ruchy);
                        } 
                    }                 
                }
            }
            else if(plansza.tura == 1)//ruch z bieciem dla czarnych
            {
                if (plansza.plansza[i][j] == 'q') // biale miejsca dla damki białej
                {
                    for(int w = i-1, k = j-1;w >= 0 && k >= 0;w--,k--) //ruchy z biciem dla damki 1 przekatna do dolu
                    {
                        if(w-1>=0 && k-1>=0)
                        {
                            if(plansza.plansza[w-1][k-1] == ' ' && (plansza.plansza[w][k]=='Q' || plansza.plansza[w][k]=='P'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w-1;
                                ruchy.y = k-1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                        
                    }
                    for(int w=i+1, k=j+1; w<8 && k<8; w++,k++) //ruchy z biciem dla damki 1 przekatna do góry
                    {
                        if(w+1<8 && k+1<8)
                        {
                            if(plansza.plansza[w+1][k+1] == ' ' && (plansza.plansza[w][k]=='Q' || plansza.plansza[w][k]=='P'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w+1;
                                ruchy.y = k+1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                    }
                    for(int w = i+1, k = j-1; w<8 && k>=0; w++,k--) //ruchy z biciem dla damki po 2 przekątnej w górę
                    {
                        if(w+1<8 && k-1>=0)
                        {
                            if(plansza.plansza[w+1][k-1] == ' ' && (plansza.plansza[w][k]=='Q' || plansza.plansza[w][k]=='P'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w+1;
                                ruchy.y = k-1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                    }   
                    for(int w = i-1, k = j+1;w >= 0 && k < 8;w--,k++) //ruchy z bicia dla damki po 2 przekątnej w dół
                    {
                        if(w-1>=0 && k+1<8)
                        {
                            if(plansza.plansza[w-1][k+1] == ' ' && (plansza.plansza[w][k]=='Q' || plansza.plansza[w][k]=='P'))
                            {
                                struct lista ruchy;
                                ruchy.p_x = i;
                                ruchy.p_y = j;
                                ruchy.x = w-1;
                                ruchy.y = k+1;
                                ruchy.a = 1;
                                dodaj_element(glowa,ruchy);   
                                // Dodaj do listy pkt i j k w 0
                                break;
                            }  
                        }
                    }
                }

                if (plansza.plansza[i][j]=='p')
                {
                    if  (i-2>=0 && j+2<8)        
                    {                     
                        if ((plansza.plansza[i-1][j+1]=='P' || plansza.plansza[i-1][j+1]=='Q') && (plansza.plansza[i-2][j+2] == ' ')) 
                        {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = i-2;
                            ruchy.y = j+2;
                            ruchy.a = 1;
                            dodaj_element(glowa,ruchy);
                        } 
                    }                 
                    if  (i-2>=0 && j-2>=0)     
                    {                     
                       if ((plansza.plansza[i-1][j-1]=='P' ||  plansza.plansza[i-1][j-1]=='Q') && (plansza.plansza[i-2][j-2] == ' ')) 
                       {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = i-2;
                            ruchy.y = j-2;
                            ruchy.a = 1;
                            dodaj_element(glowa,ruchy);
                            /*dodaj do listy pkt i j i-1 j-1 1*/
                       } 
                    }
                }
            }
        }   
    }

    return glowa->nast;
    
};

struct plansza nowa_plansza(struct plansza plansza, struct lista ruch) //wykonuje ruch przesunięcia na planszy
{   
    plansza.plansza[ruch.x][ruch.y]=plansza.plansza[ruch.p_x][ruch.p_y]; // przesuń pozycje pionka ze starej na nową
    plansza.plansza[ruch.p_x][ruch.p_y]=' ';    // wyczyść starą pozycje pionka

    if(ruch.a==1) // zbij pionek jesli ruch jest z biciem
    {
        if (ruch.x>ruch.p_x)
        {
            if (ruch.y>ruch.p_x)
            {
                plansza.plansza[ruch.x-1][ruch.y-1]=' ';
            }
            else
            {
                plansza.plansza[ruch.x-1][ruch.y+1]=' ';
            } 
        }
        else if (ruch.x<ruch.p_x) 
        {   
            if (ruch.y<ruch.p_y)
            {
                plansza.plansza[ruch.x+1][ruch.y+1]=' ';   
            }
            else
            {
                plansza.plansza[ruch.x+1][ruch.y-1]=' ';
            } 
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if(plansza.plansza[0][i]=='p') //jesli pionek dotrze do końca to zamień go na damke
        {
            plansza.plansza[0][i]='q';
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if(plansza.plansza[7][i]=='P') //jesli pionek dotrze do końca to zamień go na damke
        {
            plansza.plansza[7][i]='Q';
        }
    }
    
    if (plansza.tura==0) // tura bialych, zamień po zakończonym ruchu
    {
        plansza.tura=1;
    }
    else if (plansza.tura==1) // tura czarnych, zamień po ruchu
    {
        plansza.tura=0;
    }
    return plansza;
};  

int ruch_komputera(struct elementlisty* glowa, struct plansza plansza, int glebokosc) //jakieś wypociny żeby komputer zrobił ruch
{   
    if (glebokosc==0)
    {
        return ocena(plansza) ; // gdy dzrewo się konczy 
    }
    else  // gdy tura jest ze strony wykonujacego ruch
    {   
        int naj_poziom=-100;
        struct lista najlepsza;
        while (glowa)
        {
            struct plansza kidplansza=nowa_plansza(plansza, glowa->bicie);
            int move;
            struct elementlisty* glowa2=ruchy(kidplansza);

            move = ruch_komputera(glowa2,kidplansza,glebokosc-1);

            usun_listy(glowa2);
            if(move>naj_poziom)
            {
                naj_poziom=move;
                najlepsza=glowa->bicie;
            }
            
            najnajlepsza=najlepsza;

            glowa=glowa->nast;
        }

        if(plansza.tura==0)
        {
            return naj_poziom;
        }
        else
        {   
            return -1*naj_poziom;
        }
    }
    
};

/* PSEUDOKOD OD PROWADZACEGO
 
int AlphaBeta(state s, int depth, int alpha, int beta)
{
    if(is_terminal_node(s) || depth==0) 
    return(ocena(s));
    for(dziecko=1; dziecko<=listaruchow(s); dziecko++) 
    {
    val = -AlphaBeta(dziecko,depth-1,-beta,-alpha);
    if (val >= alpha) alpha = val;
    if (alpha > beta) return beta
    }
    return alpha;
}
 
int negamax(struct szachownica* sz, char glebokosc, int alfa, int beta)
{​​​​​​​

    if (glebokosc==0 )
        return ocena(sz);

    ocenawezla = -MAX_OCENA;

    for(struct listaruchow *lr = pseudoposuniecia(sz), *ptr = lr; lr; lr = lr->nast, free(ptr), ptr = lr)
    {​​​​​​​
        dziecko = wykonajruch(sz, &lr->ruch);
        nowaocena = -negamax(&dziecko, glebokosc - 1, -beta, -alfa);
        if (nowaocena > ocenawezla)
            ocenawezla = nowaocena;
        if (ocenawezla > alfa)
            alfa = ocenawezla;
        if (alfa >= beta)
        {​​​​​​​
            while(lr)
        {​​​​​​​
        ptr = lr;
        lr = lr->nast;
        free(ptr);
    }​​​​​​​
    break;
    }​​​​​​​ 
    }​​​​​​​
    return ocenawezla;
}​​​​​​​ 
*/

// Remember to make init call with alpha = -inf and beta = +inf to start the algorithm
// init call: currentAlphaBeta = alpha_beta(board, node, nodesDepth, -inf, +inf);
// Ininity value can easily obtained with inf = INFINITY that comes with <math.h> header

int alpha_beta(struct plansza const boardStatus, struct elementlisty* node, int depth, int alpha, int beta)
{
    int returnedAlpha = 0;
    int currentDepth = depth;

    if (depth == 0 || node->nast == NULL)
    {
        return ocena(boardStatus);
    }
    
    // iterate over available moves and re-calculate current alpha_beta value
    for (struct elementlisty* nodeChild = node->nast; nodeChild != NULL; nodeChild = nodeChild->nast, --currentDepth)
    {
        returnedAlpha = (-1) * alpha_beta(boardStatus, nodeChild, currentDepth, (-1) * beta, (-1) * alpha);

        if (alpha >= returnedAlpha)
        {
            alpha = returnedAlpha;
        }

        if (alpha > beta) 
            return beta;
    }

    return alpha;
}

int ile(struct elementlisty* glowa)
{   
    int i=0;
    while(glowa->nast)
        {
            i++;
            glowa=glowa->nast;
        }
    return i;
};

void usun_listy(struct elementlisty* glowa)
{
    struct elementlisty* glowa2=glowa;
    int how=ile(glowa);
    int i=0;

    for(int k=0; k<how; k++)
    {
        if(glowa)
        {   
            while(glowa->nast)
            {
                i++;
                glowa=glowa->nast;
            }
            free(glowa);
            glowa=glowa2;
            for (int j=0; j <i-1; j++)
            {
                glowa=glowa->nast;
            }
            glowa->nast=NULL;
            glowa=glowa2;
            i=0;
        }
    }
    
};
int main(void)
{
    //2 do poprawy do poprawy wybor przez grtacza zeby nie wpisał polecenia dla nie swojego pionka itp
    struct plansza plansza;
    plansza=przypisz();
    printf("Cześć, zagramy w warcaby!\n");
    printf("Oto zasady gry:\n\n");
    printf("Komputer jest kolorem białym\n");
    printf("Nie ma zbić podwójnych, po każdym ruchu jest zmiana tury\n");
    printf("Pionki poruszają się do przodu na skosy i tak samo biją figury\n");
    printf("Damka może poruszać się po dowolnej ilości pól na skosy do przodu i do tyłu\n");
    printf("Damka jest warta dwa razy więcej niż pionek\n\n");

    struct plansza plansza2;
    struct elementlisty* glowa;
    struct lista gracz;
    int i=1;

    while (ocena(plansza)!=100)
    {   
        printf("\n\n%d Ruch\n",i);
        wypisz(plansza);
        
        printf("Podaj współrzędne pionka który chcesz presunąć po spacji\n");
        scanf("%d %d", &gracz.p_x, &gracz.p_y);
        printf("Podaj współrzędne na które pole ma się prześć ten pionek\n");
        scanf("%d %d", &gracz.x, &gracz.y);
        printf("Napisz czy ruch jest z biciem, jeśli tak napisz 1 jeżeli nie to 0\n");
        scanf("%d", &gracz.a);

        plansza2=nowa_plansza(plansza, gracz);
        
        wypisz(plansza2);

        glowa=ruchy(plansza2);
        wypisz_liste(glowa);

        ruch_komputera(glowa, plansza2, 6);
        usun_listy(glowa);

        plansza=nowa_plansza(plansza2, najnajlepsza);
        i++;
    }
    printf("Wygrał ");
};//149 BŁĄD gdy do gry weszła damka llub pamiec sie skonczyla; 
//dodac jakas wartosc dla zaminy pionka w damke dla komputera
// zabezpieczenie gdy lista jest pusta
//segmentation foult 791 line