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

void zapisz(const char *nazwa, const naglowekObrazu &opcje)
{
    vector<Uint8> dane;
    for (int y = 0; y < wysokosc; y++)
        for (int x = 0; x < szerokosc; x++)
        {
            SDL_Color k = getPixel(x, y);
            if (opcje.glebiaBitowa == 16)
            {
                Uint16 px = ((k.r >> 3) << 11) | ((k.g >> 2) << 5) | (k.b >> 3);
                dane.push_back(px & 0xFF);
                dane.push_back((px >> 8) & 0xFF);
            }
            else
            {
                if (opcje.modelBarwny == 1) // YCbCr
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
    if (opcje.predykcja > 0)
    {
        danePredykcja.assign(dane.size(), 0);
        int bpp = (opcje.glebiaBitowa == 16) ? 2 : 3;
        filtrPaeth(dane.data(), danePredykcja.data(), szerokosc, wysokosc, bpp);
    }

    vector<Uint8> daneKompresja;
    if (opcje.kompresja == 1)
        daneKompresja = ByteRunKompresja(danePredykcja);
    else if (opcje.kompresja == 2)
        daneKompresja = RLEKompresja(danePredykcja);
    else if (opcje.kompresja == 3)
        daneKompresja = LZWKompresja(danePredykcja);
    else
        daneKompresja = danePredykcja;

    ofstream plik(nazwa, ios::binary);
    plik.write((char *) &opcje, sizeof(naglowekObrazu));
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

    streamoff aktualnaPozycja = plik.tellg();
    plik.seekg(0, ios::end);
    streamoff koniecPliku = plik.tellg();
    plik.seekg(aktualnaPozycja, ios::beg);

    size_t rozmiarDanych = koniecPliku - aktualnaPozycja;
    vector<Uint8> daneKompresja(rozmiarDanych);
    plik.read((char *) daneKompresja.data(), rozmiarDanych);

    plik.close();

    vector<Uint8> daneDekompresja;
    if (opcje.kompresja == 0)
        daneDekompresja = daneKompresja;
    else if (opcje.kompresja == 1)
        daneDekompresja = ByteRunDekompresja(daneKompresja);
    else if (opcje.kompresja == 2)
        daneDekompresja = RLEDekompresja(daneKompresja);
    else if (opcje.kompresja == 3)
        daneDekompresja = LZWDekompresja(daneKompresja);

    vector<Uint8> dane(daneDekompresja.size());
    if (opcje.predykcja > 0)
    {
        int bpp = (opcje.glebiaBitowa == 16) ? 2 : 3;
        defiltrPaeth(daneDekompresja.data(), dane.data(), szerokosc, wysokosc, bpp);
    }
    else
        dane = daneDekompresja;

    int index = 0;
    for (int y = 0; y < wysokosc; y++)
        for (int x = 0; x < szerokosc; x++)
        {
            if (opcje.glebiaBitowa == 16)
            {
                Uint8 low = dane[index++];
                Uint8 high = dane[index++];
                Uint16 px = (high << 8) | low;
                setRGB565(x, y, px);
            }
            else
            {
                Uint8 r = dane[index++];
                Uint8 g = dane[index++];
                Uint8 b = dane[index++];
                if (opcje.modelBarwny == 1) // YCbCr
                    setYCbCr(x, y, r, g, b);
                else
                    setPixel(x, y, r, g, b);
            }
        }

    SDL_UpdateWindowSurface(window);
}
