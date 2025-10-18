// podstawowe funkcje
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-MedianCut.h"
#include "SM2025-Pliki.h"
#include  <algorithm>

SDL_Color HSLtoRGB(HSL hsl) {
    float H = hsl.H;
    float S = hsl.S;
    float L = hsl.L;

    float C = (1 - std::fabs(2 * L - 1)) * S;
    float X = C * (1 - std::fabs(fmod(H / 60.0f, 2) - 1));
    float m = L - C / 2.0f;

    float r = 0, g = 0, b = 0;

    if (H < 60) { r = C; g = X; b = 0; }
    else if (H < 120) { r = X; g = C; b = 0; }
    else if (H < 180) { r = 0; g = C; b = X; }
    else if (H < 240) { r = 0; g = X; b = C; }
    else if (H < 300) { r = X; g = 0; b = C; }
    else { r = C; g = 0; b = X; }

    SDL_Color rgb;
    rgb.r = (uint8_t)((r + m) * 255);
    rgb.g = (uint8_t)((g + m) * 255);
    rgb.b = (uint8_t)((b + m) * 255);
    return rgb;
}

HSL RGBtoHSL(SDL_Color rgb) {
    float r = rgb.r / 255.0f;
    float g = rgb.g / 255.0f;
    float b = rgb.b / 255.0f;

    float maxVal = std::max({r, g, b});
    float minVal = std::min({r, g, b});
    float delta = maxVal - minVal;

    HSL hsl;
    hsl.L = (maxVal + minVal) / 2.0f;

    if (delta == 0) {
        hsl.H = 0;
        hsl.S = 0;
    } else {
        hsl.S = delta / (1 - std::fabs(2 * hsl.L - 1));

        if (maxVal == r)
            hsl.H = 60 * fmod(((g - b) / delta), 6);
        else if (maxVal == g)
            hsl.H = 60 * (((b - r) / delta) + 2);
        else
            hsl.H = 60 * (((r - g) / delta) + 4);

        if (hsl.H < 0)
            hsl.H += 360;
    }

    return hsl;
}

void setHSL(int xx, int yy, float h, float s, float l) {
    HSL hsl{h, s, l};

     SDL_Color rgb = HSLtoRGB(hsl);

     //std::cout<<"X:"<<xx<<" y:"<<yy<<"R:"<<(int)rgb.r<<" G:"<<(int)rgb.g <<"B:"<<(int)rgb.b<<endl;
    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

HSL getHSL(int xx, int yy) {
    SDL_Color kolor = getPixel(xx, yy);
    HSL hsl = RGBtoHSL(kolor);

    return hsl;
}


void Funkcja1()
{
	//hsl
	
    std::cout<<"start"<<endl;
    for(int x= 0; x<szerokosc/2; x++)
		for(int y= 0; y<wysokosc/2; y++)
		{
			HSL kolor_hsl=getHSL(x,y);
			setHSL(x+szerokosc/2,y,kolor_hsl.H,kolor_hsl.S,kolor_hsl.L);
		}

    std::cout<<"Koniec"<<endl;

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    //... YCbCr
    for(int x=0; x<szerokosc/2; x++)
        for(int y=0; y<wysokosc/2; y++)
        {
            YCbCr YCbCr = getYCbCr(x, y);
            setYCbCr(x + szerokosc/2, y, YCbCr.Y, YCbCr.Cb, YCbCr.Cr);
        }

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    //...

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
