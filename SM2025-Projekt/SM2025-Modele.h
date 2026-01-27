#ifndef SM2025_PROJEKT_SM2025_MODELE_H
#define SM2025_PROJEKT_SM2025_MODELE_H

#include <SDL2/SDL.h>
#include "SM2025-Zmienne.h"

void setYCbCr(int xx, int yy, float y, float cb, float cr);

YCbCr getYCbCr(int xx, int yy);

void setRGB565(int xx, int yy, Uint16 rgb565);

Uint16 getRGB565_(int xx, int yy);

#endif //SM2025_PROJEKT_SM2025_MODELE_H
