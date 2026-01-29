#ifndef SM2025_PROJEKT_SM2025_KOMPRESJE_H
#define SM2025_PROJEKT_SM2025_KOMPRESJE_H

#include <vector>
#include <SDL2/SDL.h>

using namespace std;

vector<Uint8> RLEKompresja(const vector<Uint8> &wejscie);

vector<Uint8> RLEDekompresja(const vector<Uint8> &wejscie);

void filtrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);

void defiltrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp);

#endif //SM2025_PROJEKT_SM2025_KOMPRESJE_H
