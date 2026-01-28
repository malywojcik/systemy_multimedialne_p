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

void setRGB555(int xx, int yy, Uint16 rgb555)
{
    Uint8 r5 = (rgb555 >> 10) & 0x1F;
    Uint8 g5 = (rgb555 >> 5) & 0x1F;
    Uint8 b5 = (rgb555) & 0x1F;

    Uint8 r = (r5 << 3) | (r5 >> 2);
    Uint8 g = (g5 << 3) | (g5 >> 2);
    Uint8 b = (b5 << 3) | (b5 >> 2);

    setPixel(xx, yy, r, g, b);
}

Uint16 getRGB555_(int xx, int yy)
{
    SDL_Color k = getPixel(xx, yy);

    Uint16 r5 = (k.r >> 3) & 0x1F;
    Uint16 g5 = (k.g >> 3) & 0x1F;
    Uint16 b5 = (k.b >> 3) & 0x1F;

    return (r5 << 10) | (g5 << 5) | b5;
}
