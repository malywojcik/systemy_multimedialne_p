// funkcje do redukcji kolor�w i tworzenia palet
#include "SM2025-Paleta.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"
#include <cmath>

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
    for (int y = 0; y < wysokosc; ++y)
        for (int x = 0; x < szerokosc; ++x)
        {
            k = getPixel(x, y);
            thr = (bayer[y & 3][x & 3] / 16.0f) - 0.5f;

            int r_new = k.r + (int) (thr * 8.0f);
            int g_new = k.g + (int) (thr * 8.0f);
            int b_new = k.b + (int) (thr * 8.0f);

            if (r_new < 0) r_new = 0;
            if (r_new > 255) r_new = 255;
            if (g_new < 0) g_new = 0;
            if (g_new > 255) g_new = 255;
            if (b_new < 0) b_new = 0;
            if (b_new > 255) b_new = 255;

            Uint8 r5 = (r_new >> 3);
            Uint8 g5 = (g_new >> 3);
            Uint8 b5 = (b_new >> 3);

            Uint8 r = (r5 << 3) | (r5 >> 2);
            Uint8 g = (g5 << 3) | (g5 >> 2);
            Uint8 b = (b5 << 3) | (b5 >> 2);

            setPixel(x, y, r, g, b);
        }

    SDL_UpdateWindowSurface(window);
}
