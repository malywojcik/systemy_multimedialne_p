#ifndef SM2025_PROJEKT_SM2025_KOMPRESJE_H
#define SM2025_PROJEKT_SM2025_KOMPRESJE_H

#include <vector>
#include <SDL2/SDL.h>
#include "SM2025-Zmienne.h"

using namespace std;

// Kompresje
vector<Uint8> ByteRunKompresja(const vector<Uint8> &wejscie);

vector<Uint8> RLEKompresja(const vector<Uint8> &wejscie);

vector<Uint8> LZWKompresja(const vector<Uint8> &wejscie);

// Dekompresje
vector<Uint8> ByteRunDekompresja(const vector<Uint8> &wejscie);

vector<Uint8> RLEDekompresja(const vector<Uint8> &wejscie);

vector<Uint8> LZWDekompresja(const vector<Uint8> &wejscie);

// LZW
void LZWinicjalizacja();

int dodajDoSlownika(slowo nowy, bool czyWyslietlac = false);

slowo noweSlowo();

slowo noweSlowo(Uint8 znak);

slowo polaczSlowo(slowo aktualneSlowo, Uint8 znak);

int znajdzWSlowniku(slowo szukany);

bool porownajSlowa(slowo slowo1, slowo slowo2);

// Predykcja
Uint8 predyktorPaeth(Uint8 a, Uint8 b, Uint8 c);

void filtrPaeth(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);

void defiltrPaeth(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);


#endif //SM2025_PROJEKT_SM2025_KOMPRESJE_H
