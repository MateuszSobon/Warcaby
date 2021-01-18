#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include <math.h>

#define CZARNE 1
#define BIALE 0
#define OCENA 1000

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
     printf("    A   B   C   D   E   F   G   H   \n");
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
    plansza.tura=0;
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
    
    plansza.tura=0;
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
                    if ((i+1<8 && j+1<8) && ((i+2<8 && j+2<8))) //sprawdzamy czy nie wychodza poza plansze
                    {
                        if ((plansza.plansza[i+1][j+1]=='p')||(plansza.plansza[i+1][j+1]=='q')&&(plansza.plansza[i+2][j+2] == ' ')) 
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
                    if ((i+1<8 && j-1>=0) && (i+2<8 && j-2>=0))                 
                    {                    
                        if ((plansza.plansza[i+1][j-1]=='p')||(plansza.plansza[i+1][j-1]=='q')&&(plansza.plansza[i+2][j-2] == ' ')) 
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
                    if ((i-1>=0 && j+1<8) && (i-2>=0 && j+2<8))                
                    {                     
                        if ((plansza.plansza[i-1][j+1]=='p')||(plansza.plansza[i-1][j+1]=='q')&&(plansza.plansza[i-2][j+2] == ' ')) 
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
                    if ((i-1>=0 && j-1>=0) && (i-2>=0 && j-2>=0))            
                    {                     
                       if ((plansza.plansza[i-1][j-1]=='p')||(plansza.plansza[i-1][j-1]=='q')&&(plansza.plansza[i-2][j-2] == ' ')) 
                       {
                            struct lista ruchy;
                            ruchy.p_x = i;
                            ruchy.p_y = j;
                            ruchy.x = i-2;
                            ruchy.y = j-2;
                            ruchy.a = 1;
                            dodaj_element(glowa,ruchy);
                            /*dodaj do listy pkt i j i+1 j+1 1*/
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
                    if ((i+1<8 && j+1<8) && ((i+2<8 && j+2<8))) //sprawdzamy czy nie wychodza poza plansze
                    {
                        if ((plansza.plansza[i+1][j+1]=='P')||(plansza.plansza[i+1][j+1]=='Q')&&(plansza.plansza[i+2][j+2] == ' ')) 
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
                    if ((i+1<8 && j-1>=0) && (i+2<8 && j-2>=0))                 
                    {                    
                        if ((plansza.plansza[i+1][j-1]=='P')||(plansza.plansza[i+1][j-1]=='Q')&&(plansza.plansza[i+2][j-2] == ' ')) 
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
                    if ((i-1>=0 && j+1<8) && (i-2>=0 && j+2<8))                
                    {                     
                        if ((plansza.plansza[i-1][j+1]=='P')||(plansza.plansza[i-1][j+1]=='Q')&&(plansza.plansza[i-2][j+2] == ' ')) 
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
                    if ((i-1>=0 && j-1>=0) && (i-2>=0 && j-2>=0))            
                    {                     
                       if ((plansza.plansza[i-1][j-1]=='P')||(plansza.plansza[i-1][j-1]=='Q')&&(plansza.plansza[i-2][j-2] == ' ')) 
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
    printf("Od funkcji ruchy\n");
    wypisz_liste(glowa);
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

int minimal(struct plansza plansza, struct elementlisty* glowa) //znajduje najlepszy ruch dla przeciwnika 
{   int najwieksza=0, pomoc=0;
    while(glowa->nast)
    {
        struct plansza plansza2 =nowa_plansza(plansza, glowa->bicie); //wykonuje ruch pierwszy z listy
        pomoc= ocena(plansza2); // oceniam go i zapisuje do zmiennej
        if (pomoc>najwieksza) // sprawdzam czy ta wartość jest większa od poprzedniej, 
        {
            najwieksza=pomoc; // jesli tak, zamieniam ją na największą 
        }
        glowa=glowa->nast;
    }
    return najwieksza; // zwracam najlepszy ruch dla tego zawodnika
};

int znak(int liczba)
{
 if (liczba %2!=0)
 {
     return -1;
 }
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
            wypisz(kidplansza);
            move = ruch_komputera(ruchy(kidplansza),kidplansza,glebokosc-1);

            if(move>naj_poziom)
            {
                naj_poziom=move;
                najlepsza=glowa->bicie;
            }
            
            

            glowa=glowa->nast;
        }
        printf("%d %d\n%d %d\n%d\n\n", najlepsza.p_x, najlepsza.p_y, najlepsza.x, najlepsza.y, najlepsza.a);
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

int main(void)
{
    struct plansza proba2=pusta();

    proba2.plansza[1][1]='p';
    proba2.plansza[0][3]='p';
    proba2.plansza[2][2]='P';
    proba2.plansza[3][0]='P';

    wypisz(proba2);
    struct elementlisty* glowa=ruchy(proba2);

    ruch_komputera(glowa, proba2, 5);
};