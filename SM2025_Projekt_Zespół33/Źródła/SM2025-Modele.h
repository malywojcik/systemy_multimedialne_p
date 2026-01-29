#ifndef SM2025_PROJEKT_SM2025_MODELE_H
#define SM2025_PROJEKT_SM2025_MODELE_H

#include <SDL2/SDL.h>
#include "SM2025-Zmienne.h"

void setYCbCr(int xx, int yy, float y, float cb, float cr);

YCbCr getYCbCr(int xx, int yy);

void setRGB555(int xx, int yy, Uint16 rgb555);

Uint16 getRGB555_(int xx, int yy);

#endif //SM2025_PROJEKT_SM2025_MODELE_H
