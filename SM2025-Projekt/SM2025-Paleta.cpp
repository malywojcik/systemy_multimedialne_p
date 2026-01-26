// funkcje do redukcji kolor�w i tworzenia palet
#include "SM2025-Paleta.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"

//gk
void narzuconaV1()
{
    SDL_Color kolor;
    int R, G, B;
    int kolor5bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++)
        for(int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            R = kolor.r;    //RRRRRRRR
            G = kolor.g;    //GGGGGGGG
            B = kolor.b;    //BBBBBBBB

            //nowyX = X>>5;     x7-x0 -> x7-x5
            //5 bit -> RRGGB

            nowyR = R>>6;   //RR
            nowyG = G>>6;   //GG
            nowyB = B>>7;   //B

            R = nowyR<<6;   //RR -> RR000000
            G = nowyG<<6;   //GG -> GG000000
            B = nowyB<<7;   //B  -> B0000000

            setPixel(x + szerokosc/2, y, R, G, B);
        }
}

void narzuconaV2()
{
    SDL_Color kolor;
    int R, G, B;
    int kolor5bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++)
        for(int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            R = kolor.r;    //RRRRRRRR
            G = kolor.g;    //GGGGGGGG
            B = kolor.b;    //BBBBBBBB

            //nowyX = X>>5;     x7-x0 -> x7-x5
            //5 bit -> RRGGB

            nowyR = R>>6;   //RR
            nowyG = G>>6;   //GG
            nowyB = B>>7;   //B

            R = nowyR*255.0/3.0;
            G = nowyG*255.0/3.0;
            B = nowyB*255.0/1.0;

            setPixel(x, y + wysokosc/2, R, G, B);
        }
}

void narzuconaV3()
{
    SDL_Color kolor;
    int R, G, B;
    int kolor5bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++)
        for(int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            R = kolor.r;    //RRRRRRRR
            G = kolor.g;    //GGGGGGGG
            B = kolor.b;    //BBBBBBBB

            //nowyX = X>>5;     x7-x0 -> x7-x5
            //5 bit -> RRGGB

            nowyR = round(R*3.0/255.0);
            nowyG = round(G*3.0/255.0);
            nowyB = round(B*1.0/255.0);

            R = nowyR*255.0/3.0;
            G = nowyG*255.0/3.0;
            B = nowyB*255.0/1.0;

            setPixel(x + szerokosc/2, y + wysokosc/2, R, G, B);
        }
}

void paletaNarzucona5bit()
{

    SDL_Color k; int R, G, B, nr, ng, nb;
    int offX = szerokosc / 2, offY = 0;
    for (int y = 0; y < wysokosc / 2; ++y)
        for (int x = 0; x < szerokosc / 2; ++x)
        {
            k = getPixel(x, y);
            nr = int(std::round(k.r * 3.0 / 255.0));
            ng = int(std::round(k.g * 3.0 / 255.0));
            nb = k.b >= 128 ? 1 : 0;
            R = nr * 85; G = ng * 85; B = nb * 255;
            setPixel(x + offX, y + offY, R, G, B);
        }
}

void paletaSzara5bit()
{
    SDL_Color k; int yval, lvl;
    int offX = 0, offY = wysokosc / 2;
    for (int y = 0; y < wysokosc / 2; ++y)
        for (int x = 0; x < szerokosc / 2; ++x)
        {
            k = getPixel(x, y);
            yval = int(std::round(0.299 * k.r + 0.587 * k.g + 0.114 * k.b));
            lvl  = int(std::round(yval * 31.0 / 255.0));
            yval = lvl * 255 / 31;
            setPixel(x + offX, y + offY, yval, yval, yval);
        }
}


void paletaSzara5bitDithering()
{
    const int bayer[4][4] = { {0,8,2,10},
                            {12,4,14,6},
                            {3,11,1,9},
                            {15,7,13,5} };
    SDL_Color k;
    float yval, off;
    int lvl, out;
    int offX = szerokosc / 2, offY = wysokosc / 2;
    for (int y = 0; y < wysokosc / 2; ++y)
        for (int x = 0; x < szerokosc / 2; ++x)
        {
            k = getPixel(x, y);
            yval = 0.299f * k.r + 0.587f * k.g + 0.114f * k.b;
            off  = (bayer[y & 3][x & 3] - 7.5f) / 16.0f;
            yval = std::clamp(yval + off * (255.0f / 31.0f), 0.0f, 255.0f);
            lvl  = int(std::round(yval * 31.0f / 255.0f));
            out  = lvl * 255 / 31;
            setPixel(x + offX, y + offY, out, out, out);
        }
}


void paletaNarzucona5bitDithering()
{
    const int bayer[4][4] = { {0,8,2,10},
                            {12,4,14,6},
                            {3,11,1,9},
                            {15,7,13,5} };
    SDL_Color k; float thr;
    int R,G,B,nr,ng,nb;
    for (int y = 0; y < wysokosc / 2; ++y)
        for (int x = 0; x < szerokosc / 2; ++x)
        {
            k = getPixel(x, y);
            thr = (bayer[y & 3][x & 3] - 7.5f) / 16.0f;
            float rm = std::clamp(k.r + thr * (255.0f / 3.0f), 0.0f, 255.0f);
            float gm = std::clamp(k.g + thr * (255.0f / 3.0f), 0.0f, 255.0f);
            float bm = std::clamp(k.b + thr * 255.0f, 0.0f, 255.0f);
            nr = int(std::round(rm * 3.0f / 255.0f));
            ng = int(std::round(gm * 3.0f / 255.0f));
            nb = bm >= 128.0f ? 1 : 0;
            R = nr * 85; G = ng * 85; B = nb * 255;
            setPixel(x, y, R, G, B);
        }
}


Uint8 z24do5bit(SDL_Color k)
{
    return ((k.r & 0xC0) >> 3) | ((k.g & 0xC0) >> 5) | ((k.b & 0x80) >> 7);
}

SDL_Color z5bitdo24(Uint8 idx)
{
    SDL_Color c;
    c.r = ((idx >> 3) & 0x03) * 85;
    c.g = ((idx >> 1) & 0x03) * 85;
    c.b = (idx & 0x01) ? 255 : 0;
    c.a = 255;
    return c;
}

void narysujPalete(int px, int py, SDL_Color pal5[32])
{
    for (int k = 0; k < 32; ++k)
    {
        int x = k % 8;
        int y = k / 8;
        for (int xx = 0; xx < 40; ++xx)
            for (int yy = 0; yy < 48; ++yy)
                setPixel(px + 40 * x + xx, py + 48 * y + yy, pal5[k].r, pal5[k].g, pal5[k].b);
    }
}

void czyscPalete()
{
    for(int k=0; k<ileKolorow; k++)
        paleta5[k] = {0, 0, 0};

    ileKolorow = 0;

    for(int k=0; k<256; k++)
    {
        paleta5s[k] = {0, 0, 0};
        paleta5k[k] = {0, 0, 0};
    }
}

Uint8 z24doK5b5(SDL_Color k)
{
    return ((k.r & 0xC0) >> 3) | ((k.g & 0xC0) >> 5) | ((k.b & 0x80) >> 7);
}

SDL_Color z5bKod24(Uint8 idx)
{
    SDL_Color c;
    c.r = ((idx >> 3) & 0x03) * 85;
    c.g = ((idx >> 1) & 0x03) * 85;
    c.b = (idx & 0x01) ? 255 : 0;
    c.a = 255;
    return c;
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2)
{
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

int dodajKolor(SDL_Color kolor)
{
    int aktualnyKolor = ileKolorow;
    paleta5[aktualnyKolor] = kolor;

    if(ileKolorow<32)
    {
        cout<<aktualnyKolor<<": [";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}

int sprawdzKolor(SDL_Color kolor)
{
    if(ileKolorow > 0)
        for(int k=0; k<ileKolorow; k++)
            if(porownajKolory(kolor, paleta5[k]))
                return k;

    return dodajKolor(kolor);
}

void paletaWykryta()
{
    czyscPalete();
    int indexKoloru;
    SDL_Color kolor;
    for(int y=0; y<wysokosc/2; y++)
        for(int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            indexKoloru = sprawdzKolor(kolor);
        }
    cout<<"\nile kolorow: "<<ileKolorow<<endl;
    if(ileKolorow <= 32)
    {
        cout<<"paleta spelnia ograniczenie 5-bit / piksel\n";
        narysujPalete(0, 210, paleta5);
    }
    else
        cout<<"paleta przekracza ograniczenie 5-bit / piksel\n";
}
