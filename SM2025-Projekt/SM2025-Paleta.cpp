// funkcje do redukcji kolor�w i tworzenia palet
#include "SM2025-Paleta.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"
#include <algorithm>

using namespace std;

// gk
void paletaNarzucona5bitDithering()
{
    const int bayer[4][4] = {
        {0, 8, 2, 10},
        {12, 4, 14, 6},
        {3, 11, 1, 9},
        {15, 7, 13, 5}
    };
    SDL_Color k;
    float thr;
    Uint8 r, g, b;
    for (int y = 0; y < wysokosc / 2; ++y)
        for (int x = 0; x < szerokosc / 2; ++x)
        {
            k = getPixel(x, y);
            thr = (bayer[y & 3][x & 3] - 7.5f) / 16.0f;
            float rm = k.r * (31.0f / 255.0f) + thr;
            float gm = k.g * (63.0f / 255.0f) + thr;
            float bm = k.b * (31.0f / 255.0f) + thr;
            r = (Uint8) min(31.0f, max(0.0f, rm));
            g = (Uint8) min(63.0f, max(0.0f, gm));
            b = (Uint8) min(31.0f, max(0.0f, bm));
            setPixel(x, y, r, g, b);
        }
}

Uint8 z24do5bit(SDL_Color k)
{
    return ((k.r & 0xC0) >> 3) | ((k.g & 0xC0) >> 5) | ((k.b & 0x80) >> 7);
}

SDL_Color z5bitdo24(Uint8 idx)
{
    SDL_Color c;
    c.r = ((idx >> 3) & 0x03) * 85;
    c.g = ((idx >> 1) & 0x03) * 85;
    c.b = (idx & 0x01) ? 255 : 0;
    c.a = 255;
    return c;
}
