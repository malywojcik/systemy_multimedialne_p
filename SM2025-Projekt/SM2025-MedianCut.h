// metody do algorytmu kwantyzacji (MedianCut)
#ifndef SM2025_MEDIANCUT_H_INCLUDED
#define SM2025_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>

//gk
void paletaMedianCutBW();
void sortujKubekBW(int start, int koniec);
void MedianCutBW(int start, int koniec, int iter);
Uint8 najwiekszaRoznica(int start, int koniec);
void sortujKubek(int start, int koniec, Uint8 skladowa);
void MedianCut(int start, int koniec, int iteracja);
void paletaMedianCut();
int znajdzSasiad(SDL_Color kolor);
void paletaMedianCutBW5();
void paletaMedianCut5();

#endif // SM2025_MEDIANCUT_H_INCLUDED
