// zmienne globalne
#ifndef SM2025_ZMIENNE_H_INCLUDED
#define SM2025_ZMIENNE_H_INCLUDED

#include <SDL2/SDL.h>

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2025 - Projekt - Zespol XX"

extern SDL_Window *window;
extern SDL_Surface *screen;

extern SDL_Color paleta8[szerokosc * wysokosc];
extern int ileKolorow;

extern SDL_Color paleta8k[256];
extern SDL_Color paleta8s[256];

// p1
struct YUV
{
    float Y;
    float U;
    float V;
};

struct YIQ
{
    float Y;
    float I;
    float Q;
};

struct YCbCr
{
    float Y;
    float Cb;
    float Cr;
};

struct HSL
{
    float H;
    float S;
    float L;
};

struct RGB
{
    Uint8 R;
    Uint8 G;
    Uint8 B;
};

// p7
struct slowo
{
    Uint16 kod = 0;
    Uint8 dlugosc = 0;
    Uint8 element[4096];
    bool wSlowniku = false;
};

extern int rozmiarSlownika;
extern slowo slownik[65535];

#endif // SM2025_ZMIENNE_H_INCLUDED
