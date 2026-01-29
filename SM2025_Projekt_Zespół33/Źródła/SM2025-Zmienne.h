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

#pragma pack(push, 1)
struct naglowekObrazu
{
    char identyfikator[4];
    Uint16 szer;
    Uint16 wyso;
    Uint8 tryb;
    Uint8 predykcja;
    Uint8 kompresja;
    Uint32 rozmiarDanych;
};
#pragma pack(pop)

struct opcjeProgramu
{
    bool czy15bit;
    bool czyYCbCR;
    bool czyDithering;
    bool czyPredykcja;
    bool czyKompresja;
};

#endif // SM2025_ZMIENNE_H_INCLUDED
