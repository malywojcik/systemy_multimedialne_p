// podstawowe funkcje
#ifndef SM2025_FUNKCJE_H_INCLUDED
#define SM2025_FUNKCJE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel(int x, int y);
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);
void ladujBMP(char const* nazwa, int x, int y);

//p1
struct YUV
{
    float Y;
    float U;
    float V;
};
struct YIQ
{
    float Y;
    float I;
    float Q;
};
struct YCbCr
{
    float Y;
    float Cb;
    float Cr;
};
struct HSL
{
    float H;
    float S;
    float L;
};
struct RGB
{
    Uint8 R;
    Uint8 G;
    Uint8 B;
};
void setYUV(int xx, int yy, float y, float u, float v);
YUV getYUV(int xx, int yy);
void setYIQ(int xx, int yy, float y, float i, float q);
YIQ getYIQ(int xx, int yy);
void setYCbCr(int xx, int yy, float y, float cb, float cr);
YCbCr getYCbCr(int xx, int yy);
void setHSL(int xx, int yy, float h, float s, float l);
HSL getHSL(int xx, int yy);

//p2
void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);
void setRGB555(int xx, int yy, Uint16 rgb555);
void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);
void setRGB565(int xx, int yy, Uint16 rgb565);
SDL_Color getRGB555(int xx, int yy);
Uint16 getRGB555_(int xx, int yy);
SDL_Color getRGB565(int xx, int yy);
Uint16 getRGB565_(int xx, int yy);
void podprobkowanieYUV(int xx, int yy, int x, int y);
void podprobkowanieYIQ(int xx, int yy, int x, int y);
void podprobkowanieYCbCr(int xx, int yy, int x, int y);
void podprobkowanieH(int xx, int yy, int x, int y);
void podprobkowanieS(int xx, int yy, int x, int y);
void podprobkowanieL(int xx, int yy, int x, int y);

#endif // SM2025_FUNKCJE_H_INCLUDED
