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
void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel(int x, int y);
SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface);
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);
void ladujBMP(char const* nazwa, int x, int y);

struct YCbCr {
    float Y;
    float Cb;
    float Cr;
    };

    struct YUV {
    float Y;
    float U;
    float V;
};
struct YIQ {
    float Y;
    float I;
    float Q;
};

void setYCbCr(int xx, int yy, float y, float cb, float cr);
YCbCr getYCbCr(int xx, int yy);
void setYUV(int xx, int yy, float y, float u, float v);
YUV getYUV(int xx, int yy);
void setYIQ(int xx, int yy, float y, float i, float q);
YIQ getYIQ(int xx, int yy);

struct RGB565 {
    Uint8 r; // 0-31
    Uint8 g; // 0-63
    Uint8 b; // 0-31
};

void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);
void setRGB565(int xx, int yy, Uint16 rgb565);
SDL_Color getRGB565(int xx, int yy);
Uint16 getRGB565_(int xx, int yy);

#endif // SM2025_FUNKCJE_H_INCLUDED
