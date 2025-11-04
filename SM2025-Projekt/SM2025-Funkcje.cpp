// podstawowe funkcje
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-MedianCut.h"
#include "SM2025-Pliki.h"
#include <cmath>
#include <algorithm>
//funkcje pomocincze
bool test6zmienna(float tempZ){
    if(6*tempZ > 1)
        return false;
    else
        return true;
}
bool test2zmienna(float tempZ){
    if(2*tempZ > 1)
        return false;
    else
        return true;
}
bool test3zmienna(float tempZ){
    if(3*tempZ > 2)
        return false;
    else
        return true;
}
float obliczanieKoloru(float tempZ, float temp0, float temp1){
    if(test6zmienna(tempZ))
        return temp1 + (temp0 - temp1) * 6 * tempZ;
    else if(test2zmienna(tempZ))
        return temp0;
    else if(test3zmienna(tempZ))
        return temp1 + (temp0 - temp1) * (0.666 - tempZ) * 6;
    else
        return temp1;
}
//funkcje głowne
void setHSL(int x, int y, float h, float s, float l){
    //std::cout << x << " "<< y << " " << h << " " << s << " " << l<<endl;
    //zmienne finalne
    uint8_t R;
    uint8_t G;
    uint8_t B;
    //zmienne na potrzeby obliczneń
    float temp0, temp1;
    float barwa;
    float zmiennaR, zmiennaG, zmiennaB;
    //przypadek gdy h i s są równe 0
    if(h == 0 && s == 0)
    {   uint8_t temp = round(l *255);
        setPixel(x,y,temp,temp,temp);
        return;
    }
    //określanie wzorów do zmiennych i obliczanie zmiennnych tymczasowych
    if(l<0.5){
        //gdy l mniejsze 0.5
        temp0 = l * (1.0 + s);
    }
    else{
        //gdy l wieksze/równe  0.5
        temp0 = l + s - l * s;
    }

    temp1 = 2 * l - temp0;
    // cout<<"temp0:"<<temp0<<" temp1:"<<temp1<<endl;
    barwa = h/360.0;
    //cout <<"barwa: "<< barwa<<endl;
    //obliczanie zmiennychR/G/B
    zmiennaR = barwa + 0.333;
    zmiennaG = barwa;
    zmiennaB = barwa - 0.333;
    //walidacja obliczonych danych
    if(zmiennaR>1)
        zmiennaR -= 1;
    else if(zmiennaR <0)
        zmiennaR += 1;
    if(zmiennaG>1)
        zmiennaG -= 1;
    else if(zmiennaG <0)
        zmiennaG += 1;
    if(zmiennaB>1)
        zmiennaB -= 1;
    else if(zmiennaB <0)
        zmiennaB += 1;
   // cout << "zmiennaR:"<<zmiennaR<<" zmiennaG:"<< zmiennaG <<"zmiennaB: "<<zmiennaB<<endl;
    // obliczanie składowych modelu RGB
    zmiennaR = obliczanieKoloru(zmiennaR,temp0,temp1);
    zmiennaG = obliczanieKoloru(zmiennaG,temp0,temp1);
    zmiennaB = obliczanieKoloru(zmiennaB,temp0,temp1);

   // cout <<"Poobliczeniu ->"<< "zmiennaR:"<<zmiennaR<<" zmiennaG:"<< zmiennaG <<"zmiennaB: "<<zmiennaB<<endl;

    // konwersja na zakres 0 -255
    R = round(zmiennaR * 255);
    G = round(zmiennaG * 255);
    B = round(zmiennaB * 255);
    //cout << "R: "<<(int)R<< "G: "<<(int)G<<"B:"<<(int)B<<endl;
    //ustawienie pixela
    setPixel(x,y,R,G,B);
}
HSL getHSL(int x, int y){
    //zmienne koncowe
    float H, S, L;
    HSL HSL;
    //zmienne pomocinicze
    SDL_Color RGB = getPixel(x,y);
    int r = RGB.r;
    int g = RGB.g;
    int b = RGB.b;
    //std::cout <<"r:"<<r<<" g:" << g << " b:" << b <<endl;
    //rzutowanie na float oraz konwersja na zakres 0-1
    float R = r/255.0f;
    float G = g/255.0f;
    float B = b/255.0f;
   //std::cout <<"r:"<<R<<" g:" << G << " b:" << B <<endl;
    float maxV = 0;
    float minV = 1117;
    maxV = max(max(R,G),B);
    minV = min(min(R,G),B);
    //cout<<"Max: " << maxV << " min: "<<minV<<endl;
    L = (minV+maxV)/2.0f;
    H=0;
    S=0;
    //okreslanie s
    if(minV!=maxV)
    {
    if(L<=0.5)
        S=(maxV-minV)/(maxV+minV);
    else
        S=(maxV-minV)/(2.0-maxV-minV);
    //określanie H
    if(R==maxV)
        H = (G-B)/(maxV-minV);
    else if(G==maxV)
        H = 2.0 + (B-R)/(maxV-minV);
    else
        H = 4.0 + (R-G)/(maxV-minV);
    H *= 60;
    }
    //walidacja H
    if(H<0)
        H +=360;

    HSL.H=H;
    HSL.S=S;
    HSL.L=L;
    //std::cout <<"h:"<<H<<" s:" << S << " l:" << L <<endl;
    return HSL;
}
void Funkcja1() {

    for(int x =0 ; x<szerokosc/2; x++)
        for(int y=0 ; y<wysokosc/2; y++)
        {
        HSL hsl = getHSL(x,y);
        setHSL(x+szerokosc/2,y,hsl.H,hsl.S,hsl.L);
        }
    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    //...

    SDL_UpdateWindowSurface(window);
}



void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y) {
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}

