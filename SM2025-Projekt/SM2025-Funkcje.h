// podstawowe funkcje
#ifndef SM2025_FUNKCJE_H_INCLUDED
#define SM2025_FUNKCJE_H_INCLUDED

#include <SDL2/SDL.h>

using namespace std;

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B);

SDL_Color getPixel(int x, int y);

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

#endif // SM2025_FUNKCJE_H_INCLUDED
