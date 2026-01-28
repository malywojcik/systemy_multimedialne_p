#include "SM2025-Modele.h"
#include "SM2025-Funkcje.h"

void setYCbCr(int xx, int yy, float y, float cb, float cr)
{
    float r = y + 1.402f * (cr - 128.0f);
    float g = y - 0.344136f * (cb - 128.0f) - 0.714136f * (cr - 128.0f);
    float b = y + 1.772f * (cb - 128.0f);

    if (r < 0.0f) r = 0.0f;
    if (r > 255.0f) r = 255.0f;
    if (g < 0.0f) g = 0.0f;
    if (g > 255.0f) g = 255.0f;
    if (b < 0.0f) b = 0.0f;
    if (b > 255.0f) b = 255.0f;

    setPixel(xx, yy, (Uint8) r, (Uint8) g, (Uint8) b);
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
    Uint8 r5 = (rgb565 >> 11) & 0x1F;
    Uint8 g6 = (rgb565 >> 5) & 0x3F;
    Uint8 b5 = (rgb565) & 0x1F;

    Uint8 R = (r5 * 255) / 31;
    Uint8 G = (g6 * 255) / 63;
    Uint8 B = (b5 * 255) / 31;

    setPixel(xx, yy, R, G, B);
}

Uint16 getRGB565_(int xx, int yy)
{
    SDL_Color k = getPixel(xx, yy);

    Uint16 r5 = (k.r * 31) / 255;
    Uint16 g6 = (k.g * 63) / 255;
    Uint16 b5 = (k.b * 31) / 255;

    return (r5 << 11) | (g6 << 5) | b5;
}
