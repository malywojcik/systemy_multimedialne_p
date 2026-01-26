// główny plik projektu
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"
#include "SM2025-Paleta.h"
#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc * 2, wysokosc * 2,
                              SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL)
    {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_UpdateWindowSurface(window);


    bool done = false;
    SDL_Event event;
    string plikIn, plikOut;
    cout<<"Podaj nazwe pliku wejsciowego: ";
    cin>>plikIn;
    cout<<"Podaj nazwe pliku wyjsciowego: ";
    cin>>plikOut;

    if (screen)
    {
        SDL_FreeSurface(screen);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
    return 0;
}
