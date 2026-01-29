// funkcje do operacji na plikach
#ifndef SM2025_PLIKI_H_INCLUDED
#define SM2025_PLIKI_H_INCLUDED

#include "SM2025-Zmienne.h"

void ladujBMP(char const *nazwa, int x, int y);

Uint8 kodujTryb(bool czy15bit, bool czyYCbCr, bool czyDithering);

void dekodujTryb(Uint8 t, bool &czy15bit, bool &czyYCbCr, bool &czyDithering);

void zapisz(const char *nazwa, const opcjeProgramu &opcje);

void wczytaj(const char *nazwa);

#endif // SM2025_PLIKI_H_INCLUDED
