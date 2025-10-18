// podstawowe funkcje
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-MedianCut.h"
#include "SM2025-Pliki.h"


void Funkcja1() {


int half = szerokosc / 2;

    // Statystyki
    int maxDiffR = 0, maxDiffG = 0, maxDiffB = 0;
    int sumDiffR = 0, sumDiffG = 0, sumDiffB = 0;
    int pixels = 0;

    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < half; ++x) {
            // Oryginalny piksel (lewo - bez zmian)
            SDL_Color original = getPixel(x, y);

            // Kwantyzacja przez getRGB565 (zwraca SDL_Color po round-trip)
            SDL_Color quantized = getRGB565(x, y);

            // Rysujemy po prawej stronie
            setPixel(x + half, y, quantized.r, quantized.g, quantized.b);

            // Obliczamy różnice
            int diffR = abs(original.r - quantized.r);
            int diffG = abs(original.g - quantized.g);
            int diffB = abs(original.b - quantized.b);

            if (diffR > maxDiffR) maxDiffR = diffR;
            if (diffG > maxDiffG) maxDiffG = diffG;
            if (diffB > maxDiffB) maxDiffB = diffB;

            sumDiffR += diffR;
            sumDiffG += diffG;
            sumDiffB += diffB;
            pixels++;
        }
    }

    // Wypisujemy statystyki
    printf("Statystyki kwantyzacji RGB565:\n");
    printf("  Maksymalny blad R: %d (z 255)\n", maxDiffR);
    printf("  Maksymalny blad G: %d (z 255)\n", maxDiffG);
    printf("  Maksymalny blad B: %d (z 255)\n", maxDiffB);
    printf("  Sredni blad R: %.3f\n", (float)sumDiffR / pixels);
    printf("  Sredni blad G: %.3f\n", (float)sumDiffG / pixels);
    printf("  Sredni blad B: %.3f\n", (float)sumDiffB / pixels);
    printf("  Liczba pikseli: %d\n\n", pixels);
    SDL_UpdateWindowSurface(window);
}
void Funkcja2() {

   int half = szerokosc / 2;

    // Wypisujemy przykładowe wartości dla pierwszych 10 pikseli
    printf("Przykladowe wartosci (pierwszych 10 pikseli):\n");
    printf("%-8s | Original RGB    | RGB565 (hex) | RGB565 (dec) | Unpacked R,G,B\n", "Piksel");
    printf("---------|-----------------|--------------|--------------|----------------\n");

    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < half; ++x) {
            // Oryginalny piksel
            SDL_Color original = getPixel(x, y);

            // Pobieramy jako Uint16 (surowa wartość RGB565)
            Uint16 rgb565 = getRGB565_(x, y);

            // Rysujemy po prawej używając setRGB565(Uint16)
            setRGB565(x + half, y, rgb565);

            // Wypisujemy tylko pierwszych 10 pikseli (dla czytelności)
            if (y == 0 && x < 10) {
                // Rozpakowujemy dla weryfikacji
                Uint8 r5 = (rgb565 >> 11) & 0x1F;
                Uint8 g6 = (rgb565 >> 5)  & 0x3F;
                Uint8 b5 =  rgb565        & 0x1F;

                printf("(%3d,%3d) | %3d,%3d,%3d     | 0x%04X       | %5d        | %2d,%2d,%2d\n",
                       x, y, original.r, original.g, original.b,
                       rgb565, rgb565, r5, g6, b5);
            }
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {


//YUV - TEST 1


//    for (int y = 0; y < wysokosc; ++y) {
//        for (int x = 0; x < szerokosc / 2; ++x) {
//            YUV yuv = getYUV(x, y);

//            setYUV(x + szerokosc / 2, y, yuv.Y, 128.0f, 128.0f);
//        }
//    }

// YIQ - TEST 1
  for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < szerokosc / 2; ++x) {
            YIQ yiq = getYIQ(x, y);

            setYIQ(x + szerokosc / 2, y, yiq.Y, 128.0f, 128.0f);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    //TEST2 - YUV
//    for (int y = 0; y < wysokosc; ++y) {
//        for (int x = 0; x < szerokosc / 2; ++x) {
//            YUV yuv = getYUV(x, y);

//            setYUV(x + szerokosc / 2, y, 128.0f, yuv.U, 128.0f);
//        }
//    }

//TEST2 - YIQ
for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < szerokosc / 2; ++x) {
            YIQ yiq = getYIQ(x, y);

            setYIQ(x + szerokosc /2, y, 128.0f, yiq.I, 128.0f);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

  //TEST 3 - YUV


//    for (int y = 0; y < szerokosc / 2; ++y) {
//        for (int x = 0; x < half; ++x) {
//            YUV yuv = getYUV(x, y);

//        setYUV(x + szerokosc / 2, y, 128.0f, 128.0f, yuv.V);
//        }
//    }

//TEST 3 - YIQ
 for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < szerokosc / 2; ++x) {
            YIQ yiq = getYIQ(x, y);

            setYIQ(x + szerokosc / 2, y, 128.0f, 128.0f, yiq.Q);
        }
    }



    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {






    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    int quarter = szerokosc / 4;

    // Statystyki dla każdej składowej
    int histR[32] = {0};  // R ma 5 bitów (0-31)
    int histG[64] = {0};  // G ma 6 bitów (0-63)
    int histB[32] = {0};  // B ma 5 bitów (0-31)

    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < quarter; ++x) {
            // Oryginalny piksel
            SDL_Color original = getPixel(x, y);

            // Kwantyzujemy do RGB565
            Uint8 r5 = original.r >> 3;  // 0-31
            Uint8 g6 = original.g >> 2;  // 0-63
            Uint8 b5 = original.b >> 3;  // 0-31

            // Histogram (zbieramy statystyki)
            histR[r5]++;
            histG[g6]++;
            histB[b5]++;



            // Część 2: Tylko R (G=0, B=0)
            setRGB565(x + quarter, y, r5, 0, 0);

            // Część 3: Tylko G (R=0, B=0)
            setRGB565(x + 2*quarter, y, 0, g6, 0);

            // Część 4: Tylko B (R=0, G=0)
            setRGB565(x + 3*quarter, y, 0, 0, b5);
        }
    }


    printf("Histogram wartosci RGB565 (top 5 najpopularniejszych):\n\n");

    // Top 5 dla R (5-bit)
    printf("R (5-bit, zakres 0-31):\n");
    for (int pass = 0; pass < 5; ++pass) {
        int maxIdx = -1, maxVal = 0;
        for (int i = 0; i < 32; ++i) {
            if (histR[i] > maxVal) {
                maxVal = histR[i];
                maxIdx = i;
            }
        }
        if (maxIdx >= 0) {
            printf("  R=%2d (RGB=%3d): %d pikseli\n", maxIdx, maxIdx << 3, maxVal);
            histR[maxIdx] = 0; // usuwamy aby znaleźć następny
        }
    }



    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < quarter; ++x) {
            SDL_Color original = getPixel(x, y);
            Uint8 g6 = original.g >> 2;
            histG[g6]++;
        }
    }

    printf("\nG (6-bit, zakres 0-63):\n");
    for (int pass = 0; pass < 5; ++pass) {
        int maxIdx = -1, maxVal = 0;
        for (int i = 0; i < 64; ++i) {
            if (histG[i] > maxVal) {
                maxVal = histG[i];
                maxIdx = i;
            }
        }
        if (maxIdx >= 0) {
            printf("  G=%2d (RGB=%3d): %d pikseli\n", maxIdx, maxIdx << 2, maxVal);
            histG[maxIdx] = 0;
        }
    }

    // Top 5 dla B (5-bit)
    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < quarter; ++x) {
            SDL_Color original = getPixel(x, y);
            Uint8 b5 = original.b >> 3;
            histB[b5]++;
        }
    }

    printf("\nB (5-bit, zakres 0-31):\n");
    for (int pass = 0; pass < 5; ++pass) {
        int maxIdx = -1, maxVal = 0;
        for (int i = 0; i < 32; ++i) {
            if (histB[i] > maxVal) {
                maxVal = histB[i];
                maxIdx = i;
            }
        }
        if (maxIdx >= 0) {
            printf("  B=%2d (RGB=%3d): %d pikseli\n", maxIdx, maxIdx << 3, maxVal);
            histB[maxIdx] = 0;
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

  int half = szerokosc / 2;

    // KROK 1: Tworzymy tablice do przechowania probkowanych wartosci U i V
    // Rozmiar: polowa szerokosci i polowa wysokosci (bo probkujemy co 2. piksel)
    int sampledWidth = (half + 1) / 2;
    int sampledHeight = (wysokosc + 1) / 2;

    // Alokujemy pamiec (dynamicznie)
    float** sampledU = new float*[sampledHeight];
    float** sampledV = new float*[sampledHeight];
    for (int i = 0; i < sampledHeight; ++i) {
        sampledU[i] = new float[sampledWidth];
        sampledV[i] = new float[sampledWidth];
    }

    printf("Rozdzielczosc oryginalna: %d x %d\n", half, wysokosc);
    printf("Rozdzielczosc chrominancji (U/V): %d x %d\n", sampledWidth, sampledHeight);
    printf("Kompresja: %.1f%% (z pelnego rozmiaru)\n\n",
           (float)(sampledWidth * sampledHeight) / (half * wysokosc) * 100.0f);

    // KROK 2: Probkowanie - pobieramy U i V co 2. piksel
    for (int y = 0; y < sampledHeight; ++y) {
        for (int x = 0; x < sampledWidth; ++x) {
            // Pozycja w oryginalnym obrazie (co 2. piksel)
            int srcX = x * 2;
            int srcY = y * 2;

            // Pobieramy YUV z pozycji (srcX, srcY)
            YUV yuv = getYUV(srcX, srcY);

            // Zapisujemy tylko U i V (Y bedzie pobierane dla kazdego piksela osobno)
            sampledU[y][x] = yuv.U;
            sampledV[y][x] = yuv.V;
        }
    }

    // KROK 3: Rekonstrukcja - rysujemy obraz po prawej stronie
    // Dla kazdego piksela: pelne Y, interpolowane U i V
    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < half; ++x) {
            // Pobieramy pelna luminancje Y dla tego piksela
            YUV yuv = getYUV(x, y);
            float Y = yuv.Y;

            // Znajdujemy najblizsza probke U i V (bez interpolacji - nearest neighbor)
            int sampX = x / 2;
            int sampY = y / 2;

            // Sprawdzamy granice
            if (sampX >= sampledWidth) sampX = sampledWidth - 1;
            if (sampY >= sampledHeight) sampY = sampledHeight - 1;

            float U = sampledU[sampY][sampX];
            float V = sampledV[sampY][sampX];

            // Rysujemy rekonstruowany piksel po prawej stronie
            setYUV(x + half, y, Y, U, V);
        }
    }


    int totalDiff = 0, maxDiff = 0, pixels = 0;
    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < half; ++x) {
            SDL_Color original = getPixel(x, y);
            SDL_Color reconstructed = getPixel(x + half, y);

            int diffR = abs(original.r - reconstructed.r);
            int diffG = abs(original.g - reconstructed.g);
            int diffB = abs(original.b - reconstructed.b);
            int diff = diffR + diffG + diffB;

            totalDiff += diff;
            if (diff > maxDiff) maxDiff = diff;
            pixels++;
        }
    }

    printf("Analiza jakosci po probkowaniu 4:2:0:\n");
    printf("  Maksymalny blad (RGB): %d\n", maxDiff);
    printf("  Sredni blad (RGB): %.2f\n", (float)totalDiff / pixels);
    printf("  Oszczednosc pamieci: %.1f%% (U i V maja 1/4 rozmiaru)\n",
           (1.0f - (1.0f + 0.25f + 0.25f) / 3.0f) * 100.0f);


    for (int i = 0; i < sampledHeight; ++i) {
        delete[] sampledU[i];
        delete[] sampledV[i];
    }
    delete[] sampledU;
    delete[] sampledV;
    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    printf("Funkcja9: Probkowanie chrominancji 4:2:0 dla YIQ\n");
    printf("  Lewo: Oryginal (pelna rozdzielczosc YIQ)\n");
    printf("  Prawo: Po probkowaniu 4:2:0 (Y pelne, I/Q co 2. piksel)\n\n");

    int half = szerokosc / 2;

    // KROK 1: Tworzymy tablice do przechowania probkowanych wartosci I i Q
    int sampledWidth = (half + 1) / 2;
    int sampledHeight = (wysokosc + 1) / 2;

    float** sampledI = new float*[sampledHeight];
    float** sampledQ = new float*[sampledHeight];
    for (int i = 0; i < sampledHeight; ++i) {
        sampledI[i] = new float[sampledWidth];
        sampledQ[i] = new float[sampledWidth];
    }

    printf("Rozdzielczosc oryginalna: %d x %d\n", half, wysokosc);
    printf("Rozdzielczosc chrominancji (I/Q): %d x %d\n", sampledWidth, sampledHeight);
    printf("Kompresja: %.1f%% (z pelnego rozmiaru)\n\n",
           (float)(sampledWidth * sampledHeight) / (half * wysokosc) * 100.0f);


    for (int y = 0; y < sampledHeight; ++y) {
        for (int x = 0; x < sampledWidth; ++x) {
            int srcX = x * 2;
            int srcY = y * 2;

            YIQ yiq = getYIQ(srcX, srcY);

            sampledI[y][x] = yiq.I;
            sampledQ[y][x] = yiq.Q;
        }
    }


    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < half; ++x) {
            // Pelna luminancja Y
            YIQ yiq = getYIQ(x, y);
            float Y = yiq.Y;

            // Pobieramy probkowane I i Q
            int sampX = x / 2;
            int sampY = y / 2;

            if (sampX >= sampledWidth) sampX = sampledWidth - 1;
            if (sampY >= sampledHeight) sampY = sampledHeight - 1;

            float I = sampledI[sampY][sampX];
            float Q = sampledQ[sampY][sampX];


            setYIQ(x + half, y, Y, I, Q);
        }
    }


    int totalDiff = 0, maxDiff = 0, pixels = 0;
    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < half; ++x) {
            SDL_Color original = getPixel(x, y);
            SDL_Color reconstructed = getPixel(x + half, y);

            int diffR = abs(original.r - reconstructed.r);
            int diffG = abs(original.g - reconstructed.g);
            int diffB = abs(original.b - reconstructed.b);
            int diff = diffR + diffG + diffB;

            totalDiff += diff;
            if (diff > maxDiff) maxDiff = diff;
            pixels++;
        }
    }

    printf("Analiza jakosci po probkowaniu 4:2:0:\n");
    printf("  Maksymalny blad (RGB): %d\n", maxDiff);
    printf("  Sredni blad (RGB): %.2f\n", (float)totalDiff / pixels);
    printf("  Oszczednosc pamieci: %.1f%% (I i Q maja 1/4 rozmiaru)\n",
           (1.0f - (1.0f + 0.25f + 0.25f) / 3.0f) * 100.0f);


    for (int i = 0; i < sampledHeight; ++i) {
        delete[] sampledI[i];
        delete[] sampledQ[i];
    }
    delete[] sampledI;
    delete[] sampledQ;

    SDL_UpdateWindowSurface(window);
}



void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y) {
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}

void setYCbCr(int xx, int yy, float y, float cb, float cr)
{
    Uint8 R, G, B;
    float r, g, b;
    r = y + 1.402 * (cr - 128);
    g = y - 0.344136 * (cb - 128) - 0.714136 * (cr - 128);
    b = y + 1.772 * (cb - 128);
    R = (r > 255) ? 255 : r ;
    G = (g > 255) ? 255 : g;
    B = (b > 255) ? 255 : b;

    R = (r < 0) ? 0 : r;
    G = (g < 0) ? 0 : g;
    B = (b < 0) ? 0 : b;

    setPixel(xx, yy, R, G, B);
}

YCbCr getYCbCr(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YCbCr kolor_YCbCr;
    kolor_YCbCr.Y = 0 + (0.299 * kolor.r) + (0.587 * kolor.g) + (0.114 * kolor.b);
    kolor_YCbCr.Cb = 128 - (0.168736 * kolor.r) - (0.331264 * kolor.g) + (0.5 * kolor.b);
    kolor_YCbCr.Cr = 128 + (0.5 * kolor.r) - (0.418688 * kolor.g) - (0.081312 * kolor.b);

    return kolor_YCbCr;
}

void setYUV(int xx, int yy, float y, float u, float v)
{

    float U = u - 128.0f;
    float V = v - 128.0f;

    float r = y + 1.13983f * V;
    float g = y - 0.39465f * U - 0.58060f * V;
    float b = y + 2.03211f * U;

    // ograniczanie do [0,255]
    if (r < 0.0f) r = 0.0f; if (r > 255.0f) r = 255.0f;
    if (g < 0.0f) g = 0.0f; if (g > 255.0f) g = 255.0f;
    if (b < 0.0f) b = 0.0f; if (b > 255.0f) b = 255.0f;

    setPixel(xx, yy, (Uint8)r, (Uint8)g, (Uint8)b);
}
YUV getYUV(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YUV out;
    out.Y = 0.299f * kolor.r + 0.587f * kolor.g + 0.114f * kolor.b;

    out.U = 128.0f + (-0.14713f * kolor.r) + (-0.28886f * kolor.g) + (0.436f * kolor.b);
    out.V = 128.0f + (0.615f * kolor.r) + (-0.51499f * kolor.g) + (-0.10001f * kolor.b);
    return out;
}

void setYIQ(int xx, int yy, float y, float i, float q)
{

    float I = i - 128.0f;
    float Q = q - 128.0f;

    float r = y + 0.956f * I + 0.619f * Q;
    float g = y - 0.272f * I - 0.647f * Q;
    float b = y - 1.106f * I + 1.703f * Q;

    // ograniczanie do [0,255]
    if (r < 0.0f) r = 0.0f; if (r > 255.0f) r = 255.0f;
    if (g < 0.0f) g = 0.0f; if (g > 255.0f) g = 255.0f;
    if (b < 0.0f) b = 0.0f; if (b > 255.0f) b = 255.0f;

    setPixel(xx, yy, (Uint8)r, (Uint8)g, (Uint8)b);
}

YIQ getYIQ(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YIQ out;
    out.Y = 0.299f * kolor.r + 0.587f * kolor.g + 0.114f * kolor.b;

    out.I = 128.0f + (0.5959f * kolor.r) + (-0.2746f * kolor.g) + (-0.3213f * kolor.b);
    out.Q = 128.0f + (0.2115f * kolor.r) + (-0.5227f * kolor.g) + (0.3112f * kolor.b);
    return out;
}
void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    /* Konwertuje RGB565 (5-6-5 bit) do RGB888 (8-8-8 bit) i rysuje piksel.

       Parametry wejsciowe:
       - r: 0-31 (5 bitow) - czerwony
       - g: 0-63 (6 bitow) - zielony
       - b: 0-31 (5 bitow) - niebieski
    */

    // Ograniczamy wartosci do dopuszczalnych zakresow
    if (r > 31) r = 31;
    if (g > 63) g = 63;
    if (b > 31) b = 31;

    // Konwersja RGB565 -> RGB888
    // Rozszerzamy bity kopiujac najstarsze bity na najmlodsze pozycje
    Uint8 R_24bit = (r << 3) | (r >> 2);  // 5 bitow -> 8 bitow
    Uint8 G_24bit = (g << 2) | (g >> 4);  // 6 bitow -> 8 bitow
    Uint8 B_24bit = (b << 3) | (b >> 2);  // 5 bitow -> 8 bitow

    setPixel(xx, yy, R_24bit, G_24bit, B_24bit);
}


void setRGB565(int xx, int yy, Uint16 rgb565)
{





    Uint8 r = (rgb565 >> 11) & 0x1F;  // 5 najstarszych bitow (maska 0x1F = 0b11111)
    Uint8 g = (rgb565 >> 5)  & 0x3F;  // 6 srodkowych bitow (maska 0x3F = 0b111111)
    Uint8 b =  rgb565        & 0x1F;  // 5 najmlodszych bitow (maska 0x1F = 0b11111)

    // Konwersja do RGB888
    Uint8 R_24bit = (r << 3) | (r >> 2);
    Uint8 G_24bit = (g << 2) | (g >> 4);
    Uint8 B_24bit = (b << 3) | (b >> 2);

    setPixel(xx, yy, R_24bit, G_24bit, B_24bit);
}


SDL_Color getRGB565(int xx, int yy)
{


    // Pobieramy oryginalny piksel (24-bit)
    SDL_Color original = getPixel(xx, yy);

    // Kwantyzujemy do RGB565 (obcinamy najmłodsze bity)
    Uint8 r5 = original.r >> 3;  // 8 bitow -> 5 bitow
    Uint8 g6 = original.g >> 2;  // 8 bitow -> 6 bitow
    Uint8 b5 = original.b >> 3;  // 8 bitow -> 5 bitow

    // Konwertujemy z powrotem do RGB888 (aby pasowalo do SDL_Color)
    SDL_Color quantized;
    quantized.r = (r5 << 3) | (r5 >> 2);
    quantized.g = (g6 << 2) | (g6 >> 4);
    quantized.b = (b5 << 3) | (b5 >> 2);
    quantized.a = 255;  // pelna nieprzezroczystosc

    return quantized;
}


Uint16 getRGB565_(int xx, int yy)
{


    // Pobieramy oryginalny piksel (24-bit)
    SDL_Color kolor = getPixel(xx, yy);

    // Kwantyzujemy do RGB565 (obcinamy najmłodsze bity)
    Uint8 r5 = kolor.r >> 3;  // 8 bitow -> 5 bitow
    Uint8 g6 = kolor.g >> 2;  // 8 bitow -> 6 bitow
    Uint8 b5 = kolor.b >> 3;  // 8 bitow -> 5 bitow

    // Pakujemy do pojedynczej wartosci 16-bit
    // Format: RRRRRGGGGGGBBBBB
    Uint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;

    return rgb565;
}

