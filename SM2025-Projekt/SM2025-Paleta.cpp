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
    Uint8 r, g, b, r5, g6, b5;
    for (int y = 0; y < wysokosc; ++y)
        for (int x = 0; x < szerokosc; ++x)
        {
            k = getPixel(x, y);
            thr = (bayer[y & 3][x & 3] - 7.5f) / 16.0f;

            float rm = k.r * (31.0f / 255.0f) + thr;
            float gm = k.g * (63.0f / 255.0f) + thr;
            float bm = k.b * (31.0f / 255.0f) + thr;

            r5 = (Uint8) min(31.0f, max(0.0f, rm));
            g6 = (Uint8) min(63.0f, max(0.0f, gm));
            b5 = (Uint8) min(31.0f, max(0.0f, bm));

            r = (r5 * 255) / 31;
            g = (g6 * 255) / 63;
            b = (b5 * 255) / 31;

            setPixel(x, y, r, g, b);
        }

    SDL_UpdateWindowSurface(window);
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
