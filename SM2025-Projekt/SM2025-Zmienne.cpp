// zmienne globalne
#include "SM2025-Zmienne.h"

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;

SDL_Color paleta8[szerokosc * wysokosc];
int ileKolorow = 0;

SDL_Color paleta8k[256];
SDL_Color paleta8s[256];

//gk
SDL_Color paleta5k[32];
SDL_Color paleta5s[32];

int ileKubelkow = 0;
Uint8  obrazekS[320 * 200];
SDL_Color obrazekK[320 * 200];

// p7
int rozmiarSlownika;
slowo slownik[65535];
