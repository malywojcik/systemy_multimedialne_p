#include "SM2025-Modele.h"
#include "SM2025-Funkcje.h"

void setYCbCr(int xx, int yy, float y, float cb, float cr)
{
    Uint8 R, G, B;
    float r, g, b;

    r = y + 1.402f * (cr - 128.0f);
    g = y - 0.344136f * (cb - 128.0f) - 0.714136f * (cr - 128.0f);
    b = y + 1.772f * (cb - 128.0f);

    R = (r > 255) ? 255 : r;
    G = (g > 255) ? 255 : g;
    B = (b > 255) ? 255 : b;

    R = (Uint8) (r < 0) ? 0 : r;
    G = (Uint8) (g < 0) ? 0 : g;
    B = (Uint8) (b < 0) ? 0 : b;

    setPixel(xx, yy, R, G, B);
}

YCbCr getYCbCr(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YCbCr ycbcr;
    ycbcr.Y = 0 + (0.299 * kolor.r) + (0.587 * kolor.g) + (0.114 * kolor.b);
    ycbcr.Cb = 128 - (0.168736 * kolor.r) - (0.331264 * kolor.g) + (0.5 * kolor.b);
    ycbcr.Cr = 128 + (0.5 * kolor.r) - (0.418688 * kolor.g) - (0.081312 * kolor.b);

    return ycbcr;
}

void setRGB565(int xx, int yy, Uint16 rgb565)
{
    Uint8 r = ((rgb565 >> 11) & 0x1F) << 3;
    Uint8 g = ((rgb565 >> 5) & 0x3F) << 2;
    Uint8 b = (rgb565 & 0x1F) << 3;

    setPixel(xx, yy, r, g, b);
}

Uint16 getRGB565_(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);

    return ((kolor.r >> 3) << 11 | ((kolor.g >> 2) << 5) | (kolor.b >> 3));
}
