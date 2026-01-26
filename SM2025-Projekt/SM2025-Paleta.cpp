// funkcje do redukcji kolor�w i tworzenia palet
#include "SM2025-Paleta.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"
#include <algorithm>

 using namespace std;

// gk
void paletaNarzucona5bitDithering()
{
    const int bayer[4][4] = { {0,8,2,10},
                            {12,4,14,6},
                            {3,11,1,9},
                            {15,7,13,5} };
    SDL_Color k; float thr;
    int R,G,B,nr,ng,nb;
    for (int y = 0; y < wysokosc / 2; ++y)
        for (int x = 0; x < szerokosc / 2; ++x)
        {
            k = getPixel(x, y);
            thr = (bayer[y & 3][x & 3] - 7.5f) / 16.0f;
            float rm = clamp(k.r + thr * (255.0f / 32.0f), 0.0f, 255.0f);
            float gm = clamp(k.g + thr * (255.0f / 64.0f), 0.0f, 255.0f);
            float bm = clamp(k.b + thr * (255.0f / 32.0f), 0.0f, 255.0f);
            nr = int(round(rm * 3.0f / 255.0f));
            ng = int(round(gm * 3.0f / 255.0f));
            nb = bm >= 128.0f ? 1 : 0;
            R = nr * 85; G = ng * 85; B = nb * 255;
            Uint8 r5, g6, b5;
            r5 = (Uint8(rm) >> 3) << 3;
            g6 = (Uint8(gm) >> 2) << 2;
            b5 = (Uint8(bm) >> 3) << 3;
            setPixel(x, y, r5, g6, b5);
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
