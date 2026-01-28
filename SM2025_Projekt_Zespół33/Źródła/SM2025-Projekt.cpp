#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"
#include "SM2025-Pliki.h"
#include "SM2025-Paleta.h"

using namespace std;

bool czyRozszerzenie(string nazwa, string rozszerzenie)
{
    if (nazwa.length() >= rozszerzenie.length())
        return (0 == nazwa.compare(nazwa.length() - rozszerzenie.length(), rozszerzenie.length(), rozszerzenie));

    return false;
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());

        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc * 2, wysokosc * 2, SDL_WINDOW_SHOWN);
    if (!window)
        return EXIT_FAILURE;

    screen = SDL_GetWindowSurface(window);
    if (!screen)
        return false;
    SDL_UpdateWindowSurface(window);

    string plikIn, plikOut;
    char wybor;

    cout << "--- SM2025 PROJEKT ZESPOL33 ---" << endl;

    cout << "Podaj nazwe pliku wejsciowego: ";
    cin >> plikIn;
    cout << "Podaj nazwe pliku wyjsciowego: ";
    cin >> plikOut;

    SDL_PumpEvents();

    if (czyRozszerzenie(plikIn, ".z33") || czyRozszerzenie(plikIn, ".Z33"))
    {
        cout << "Tryb: Dekodowanie pliku autorskiego." << endl;
        wczytaj(plikIn.c_str());

        if (SDL_SaveBMP(screen, plikOut.c_str()) == 0)
            cout << "Zapisano BMP: " << plikOut << endl;

        else
            cout << "Blad zapisu BMP: " << SDL_GetError() << endl;

    }
    else
    {
        cout << "Tryb: Kodowanie do formatu autorskiego." << endl;
        ladujBMP(plikIn.c_str(), 0, 0);

        naglowekObrazu opcje;

        opcje.identyfikator = 0x335A;
        opcje.szer = szerokosc;
        opcje.wyso = wysokosc;
        opcje.glebiaBitowa = 24;
        opcje.modelBarwny = 0; // RGB
        opcje.kompresja = 0; // Brak
        opcje.predykcja = 0; // Brak
        opcje.dithering = 0; // Brak
        opcje.zarezerwowane = 0;

        cout << "W jakim trybie barwnym zapisac obraz? (1 - 16-bit, 2 - 24-bit): ";
        cin >> wybor;

        if (wybor == '1')
        {
            opcje.glebiaBitowa = 16;

            cout << "Czy dithering? (t/n): ";
            cin >> wybor;
            if (wybor == 't' || wybor == 'T')
            {
                opcje.dithering = 1;
                paletaNarzucona5bitDithering();
            }

            cout << "Czy predykcja? (t/n): ";
            cin >> wybor;
            if (wybor == 't' || wybor == 'T')
                opcje.predykcja = 4;

            cout << "Czy kompresja bezstratna? (t/n): ";
            cin >> wybor;
            if (wybor == 't' || wybor == 'T')
                opcje.kompresja = 3;
        }
        else
        {
            opcje.glebiaBitowa = 24;

            cout << "Czy RGB? (t - tak, n - nie [YCbCr]): ";
            cin >> wybor;
            if (wybor == 'n' || wybor == 'N')
                opcje.modelBarwny = 1;

            cout << "Czy predykcja? (t/n): ";
            cin >> wybor;
            if (wybor == 't' || wybor == 'T')
                opcje.predykcja = 4;

            cout << "Czy kompresja bezstratna? (t/n): ";
            cin >> wybor;
            if (wybor == 't' || wybor == 'T')
                opcje.kompresja = 3;
        }

        zapisz(plikOut.c_str(), opcje);

        czyscEkran(0, 0, 0);
        wczytaj(plikOut.c_str());
        cout << "Gotowe. Sprawdz plik wyjsciowy." << endl;
    }

    SDL_UpdateWindowSurface(window);

    bool done = false;
    SDL_Event event;
    while (!done)
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                done = true;

    if (screen) SDL_FreeSurface(screen);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
