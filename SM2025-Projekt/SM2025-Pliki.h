// funkcje do operacji na plikach
#ifndef SM2025_PLIKI_H_INCLUDED
#define SM2025_PLIKI_H_INCLUDED

#include "SM2025-Zmienne.h"

void ladujBMP(char const *nazwa, int x, int y);

void zapisz(const char *nazwa, const naglowekObrazu &opcje);

void wczytaj(const char *nazwa);

#endif // SM2025_PLIKI_H_INCLUDED
