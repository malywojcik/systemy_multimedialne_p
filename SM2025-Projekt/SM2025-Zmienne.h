// zmienne globalne
#ifndef SM2025_ZMIENNE_H_INCLUDED
#define SM2025_ZMIENNE_H_INCLUDED

#include <SDL2/SDL.h>

#define szerokosc 320
#define wysokosc 200

#define tytul "SM2025 - Projekt - Zespol 33"

extern SDL_Window *window;
extern SDL_Surface *screen;

struct YCbCr
{
    float Y;
    float Cb;
    float Cr;
};

struct slowo
{
    Uint16 kod = 0;
    Uint8 dlugosc = 0;
    Uint8 element[4096];
    bool wSlowniku = false;
};

extern int rozmiarSlownika;
extern slowo slownik[65536];

struct naglowekObrazu
{
    Uint16 identyfikator;
    Uint16 szer;
    Uint16 wyso;
    Uint8 glebiaBitowa; // 16 lub 24
    Uint8 modelBarwny; // 0 = RGB, 1 = YCbCr
    Uint8 kompresja; // 0 = brak, 1 = ByteRun, 2 = RLE, 3 = LZW
    Uint8 predykcja; // 0 = brak, 4 = Paeth
    Uint8 dithering; // 0 = nie, 1 = tak
    Uint8 zarezerwowane;
};

#endif // SM2025_ZMIENNE_H_INCLUDED
