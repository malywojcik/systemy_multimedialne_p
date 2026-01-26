// funkcje do redukcji kolor�w i tworzenia palet
#ifndef SM2025_PALETA_H_INCLUDED
#define SM2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

// gk
void paletaNarzucona5bitDithering();
Uint8 z24do5bit(SDL_Color kolor);
SDL_Color z5bitdo24(Uint8 kolor5bit);

#endif // SM2025_PALETA_H_INCLUDED
