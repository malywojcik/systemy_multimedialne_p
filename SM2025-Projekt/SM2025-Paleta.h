// funkcje do redukcji kolor�w i tworzenia palet
#ifndef SM2025_PALETA_H_INCLUDED
#define SM2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

//gk
void narzuconaV1();
void narzuconaV2();
void narzuconaV3();

void paletaNarzucona5bit();
void paletaSzara5bit();
void paletaSzara5bitDithering();
void paletaNarzucona5bitDithering();

Uint8 z24do5bit(SDL_Color kolor);
SDL_Color z5bitdo24(Uint8 kolor5bit);

void narysujPalete(int px, int py, SDL_Color pal5[]);
void czyscPalete();
void narysujPalete(int px, int py, SDL_Color pal5[]);

Uint8 z24doK5b5(SDL_Color kolor);
SDL_Color z5bKod24(Uint8 idx);

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
int sprawdzKolor(SDL_Color kolor);
void paletaWykryta();

void zapiszPlik5();
void odczytajPlik5();

#endif // SM2025_PALETA_H_INCLUDED
