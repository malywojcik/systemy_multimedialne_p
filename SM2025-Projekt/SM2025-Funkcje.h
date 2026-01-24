// podstawowe funkcje
#ifndef SM2025_FUNKCJE_H_INCLUDED
#define SM2025_FUNKCJE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "SM2025-Zmienne.h"

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

void ladujBMP(char const *nazwa, int x, int y);

// p1
void setYUV(int xx, int yy, float y, float u, float v);

YUV getYUV(int xx, int yy);

void setYIQ(int xx, int yy, float y, float i, float q);

YIQ getYIQ(int xx, int yy);

void setYCbCr(int xx, int yy, float y, float cb, float cr);

YCbCr getYCbCr(int xx, int yy);

void setHSL(int xx, int yy, float h, float s, float l);

HSL getHSL(int xx, int yy);

// p2
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

// p6
void ByteRunKompresja(int wejscie[], int dlugosc, const char *nazwaPliku);

void ByteRunDekompresja(const char *nazwaPliku);

void RLEKompresja(int wejscie[], int dlugosc, const char *nazwaPliku);

void RLEDekompresja(const char *nazwaPliku);

// p7
void LZWKompresja(int wejscie[], int dlugosc, const char *nazwaPliku);

void LZWinicjalizacja();

int dodajDoSlownika(slowo nowy, bool czyWyslietlac = true);

slowo noweSlowo();

slowo noweSlowo(Uint8 znak);

slowo polaczSlowo(slowo aktualneSlowo, Uint8 znak);

void wyswietlSlowo(slowo aktualneSlowo);

int znajdzWSlowniku(slowo szukany);

bool porownajSlowa(slowo slowo1, slowo slowo2);

void LZWDekompresja(const char *nazwaPliku);

// p8
Uint8 predyktorPaeth(Uint8 a, Uint8 b, Uint8 c);
void filtrSub(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);
void filtrUp(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);
void filtrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);
void filtrPaeth(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);

void defiltrSub(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);
void defiltrUp(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);
void defiltrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);
void defiltrPaeth(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);

#endif // SM2025_FUNKCJE_H_INCLUDED
