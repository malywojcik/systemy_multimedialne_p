// funkcje do operacji na plikach
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-Pliki.h"
#include "SM2025-Kompresje.h"
#include "SM2025-Modele.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

void ladujBMP(char const *nazwa, int x, int y)
{
    SDL_Surface *bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
        printf("Unable to load bitmap: %s\n", SDL_GetError());

    else
    {
        SDL_Color kolor;
        for (int yy = 0; yy < bmp->h; yy++)
            for (int xx = 0; xx < bmp->w; xx++)
            {
                kolor = getPixelSurface(xx, yy, bmp);
                setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
            }

        SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }
}

Uint8 kodujTryb(bool czy15bit, bool czyYCbCr, bool czyDithering)
{
    Uint8 t = 0;
    if (czy15bit) t |= 1;
    if (czyYCbCr) t |= 2;
    if (czyDithering) t |= 4;

    return t;
}

void dekodujTryb(Uint8 t, bool &czy15bit, bool &czyYCbCr, bool &czyDithering)
{
    czy15bit = (t & 1);
    czyYCbCr = (t & 2);
    czyDithering = (t & 4);
}

void zapisz(const char *nazwa, const opcjeProgramu &opcje)
{
    vector<Uint8> dane;
    for (int y = 0; y < wysokosc; y++)
        for (int x = 0; x < szerokosc; x++)
        {
            SDL_Color k = getPixel(x, y);
            if (opcje.czy15bit)
            {
                Uint16 px = getRGB555_(x, y);
                dane.push_back(px & 0xFF);
                dane.push_back((px >> 8) & 0xFF);
            }
            else
            {
                if (opcje.czyYCbCR)
                {
                    YCbCr ycbcr = getYCbCr(x, y);
                    dane.push_back((Uint8) ycbcr.Y);
                    dane.push_back((Uint8) ycbcr.Cb);
                    dane.push_back((Uint8) ycbcr.Cr);
                }
                else
                {
                    dane.push_back(k.r);
                    dane.push_back(k.g);
                    dane.push_back(k.b);
                }
            }
        }

    vector<Uint8> danePredykcja = dane;
    if (opcje.czyPredykcja)
    {
        danePredykcja.assign(dane.size(), 0);
        int bpp = (opcje.czy15bit) ? 2 : 3;
        filtrAvg(dane.data(), danePredykcja.data(), szerokosc, wysokosc, bpp);
    }

    vector<Uint8> daneKompresja;
    if (opcje.czyKompresja)
        daneKompresja = RLEKompresja(danePredykcja);
    else
        daneKompresja = danePredykcja;

    naglowekObrazu nag;
    memcpy(nag.identyfikator, "DG24", 4);
    nag.szer = szerokosc;
    nag.wyso = wysokosc;
    nag.tryb = kodujTryb(opcje.czy15bit, opcje.czyYCbCR, opcje.czyDithering);
    nag.predykcja = opcje.czyPredykcja ? 1 : 0;
    nag.kompresja = opcje.czyKompresja ? 1 : 0;
    nag.rozmiarDanych = (Uint32)daneKompresja.size();

    ofstream plik(nazwa, ios::binary);
    plik.write((char *) &nag, sizeof(naglowekObrazu));
    plik.write((char *) daneKompresja.data(), daneKompresja.size());
    plik.close();

    cout << "Zapisano obraz do pliku: (" << nazwa << ") rozmiar: " << daneKompresja.size() << " bajtow" << endl;
}

void wczytaj(const char *nazwa)
{
    ifstream plik(nazwa, ios::binary);
    if (!plik)
    {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return;
    }

    naglowekObrazu opcje;
    plik.read((char *) &opcje, sizeof(naglowekObrazu));

    if (strncmp(opcje.identyfikator, "DG24", 4) != 0) {
        cout << "To nie jest plik DG24!" << endl;
        plik.close();
        return;
    }

    bool czy15bit, czyYCbCr, czyDithering;
    dekodujTryb(opcje.tryb, czy15bit, czyYCbCr, czyDithering);
    bool czyPredykcja = (opcje.predykcja == 1);
    bool czyKompresja = (opcje.kompresja == 1);


    vector<Uint8> daneKompresja(opcje.rozmiarDanych);
    plik.read((char *) daneKompresja.data(), opcje.rozmiarDanych);
    plik.close();

    vector<Uint8> daneDekompresja;
    if (czyKompresja)
        daneDekompresja = RLEDekompresja(daneKompresja);
    else
        daneDekompresja = daneKompresja;

    vector<Uint8> dane(daneDekompresja.size());
    if (czyPredykcja)
    {
        int bpp = (czy15bit) ? 2 : 3;
        defiltrAvg(daneDekompresja.data(), dane.data(), opcje.szer, opcje.wyso, bpp);
    }
    else
        dane = daneDekompresja;

    int index = 0;
    for (int y = 0; y < wysokosc; y++)
        for (int x = 0; x < szerokosc; x++)
        {
            if (czy15bit)
            {
                if (index + 1 >= dane.size())
                    break;
                Uint8 low = dane[index++];
                Uint8 high = dane[index++];
                Uint16 px = (high << 8) | low;

                setRGB555(x, y, px);
            }
            else
            {
                if (index + 2 >= dane.size())
                    break;
                Uint8 r = dane[index++];
                Uint8 g = dane[index++];
                Uint8 b = dane[index++];
                if (czyYCbCr)
                    setYCbCr(x, y, r, g, b);
                else
                    setPixel(x, y, r, g, b);
            }
        }

    SDL_UpdateWindowSurface(window);
}
