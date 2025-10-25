// zmienne globalne
#ifndef SM2025_ZMIENNE_H_INCLUDED
#define SM2025_ZMIENNE_H_INCLUDED
#include <cstdint>
#include <SDL2/SDL.h>

#define szerokosc 640
#define wysokosc 400

#define tytul "SM2025 - Projekt - Zespol XX"

extern SDL_Window* window;
extern SDL_Surface* screen;

extern SDL_Color paleta8[szerokosc*wysokosc];
extern int ileKolorow;

extern SDL_Color paleta8k[256];
extern SDL_Color paleta8s[256];

struct HSL
{
    float H;
    float S;
    float L;
};

struct RGB
{
    int R;
    int G;
    int B;
};
#endif // SM2025_ZMIENNE_H_INCLUDED
