// podstawowe funkcje
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-MedianCut.h"
#include "SM2025-Pliki.h"

void Funkcja1()
{
    //kompresja byterun
    int nieskompresowane[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3};
    int dlugosc = 24;
    cout<<"\nwejscie:\n";
    for (int c =0; c<dlugosc-1; c++)
        cout<<(int)nieskompresowane[c]<<", ";
    cout<<(int)nieskompresowane[dlugosc-1]<<endl;
    ByteRunKompresja(nieskompresowane, dlugosc);

    SDL_UpdateWindowSurface(window);
}

void Funkcja2()
{
    //kompresja byterun
    int nieskompresowane[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3, 1, 2};
    int dlugosc = 25;
    cout<<"\nwejscie:\n";
    for (int c =0; c<dlugosc-1; c++)
        cout<<(int)nieskompresowane[c]<<", ";
    cout<<(int)nieskompresowane[dlugosc-1]<<endl;
    RLEKompresja(nieskompresowane, dlugosc);

    SDL_UpdateWindowSurface(window);
}

void Funkcja3()
{
    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja4()
{
    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja5()
{
    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja6()
{
    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja7()
{
    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja8()
{
    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja9()
{
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

//p1
void setYUV(int xx, int yy, float y, float u, float v)
{
    Uint8 R, G, B;
    float r, g, b;

    r = y + 1.13983f * v;
    g = y - 0.39465f * u - 0.58060f * v;
    b = y + 2.03211f * u;

    r *= 255.0f;
    g *= 255.0f;
    b *= 255.0f;

    if (r < 0.0f) r = 0.0f;
    if (r > 255.0f) r = 255.0f;
    if (g < 0.0f) g = 0.0f;
    if (g > 255.0f) g = 255.0f;
    if (b < 0.0f) b = 0.0f;
    if (b > 255.0f) b = 255.0f;

    R = (Uint8)r;
    G = (Uint8)g;
    B = (Uint8)b;

    setPixel(xx, yy, R, G, B);
}

YUV getYUV(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YUV yuv;

    float r, g, b;
    r = kolor.r / 255.0f;
    g = kolor.g / 255.0f;
    b = kolor.b / 255.0f;

    yuv.Y = 0.299f * r + 0.587f * g + 0.114 * b;
    yuv.U = - 0.14713f * r - 0.28886f * g + 0.436f * b;
    yuv.V = 0.615f * r - 0.51499f * g - 0.10001f * b;

    return yuv;
}

void setYIQ(int xx, int yy, float y, float i, float q)
{
    Uint8 R, G, B;
    float r, g, b;

    r = y + 0.956f * i + 0.619f * q;
    g = y - 0.272f * i - 0.647f * q;
    b = y - 1.106f * i + 1.703f * q;

    r *= 255.0f;
    g *= 255.0f;
    b *= 255.0f;

    if (r < 0.0f) r = 0.0f;
    if (r > 255.0f) r = 255.0f;
    if (g < 0.0f) g = 0.0f;
    if (g > 255.0f) g = 255.0f;
    if (b < 0.0f) b = 0.0f;
    if (b > 255.0f) b = 255.0f;

    R = (Uint8)r;
    G = (Uint8)g;
    B = (Uint8)b;

    setPixel(xx, yy, R, G, B);
}

YIQ getYIQ(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YIQ yiq;

    float r, g, b;
    r = kolor.r / 255.0f;
    g = kolor.g / 255.0f;
    b = kolor.b / 255.0f;

    yiq.Y = 0.299f * r + 0.587f * g + 0.114 * b;
    yiq.I = 0.5959f * r - 0.2746f * g - 0.3213f * b;
    yiq.Q = 0.2115f * r - 0.5277f * g + 0.3112f * b;

    return yiq;
}

void setYCbCr(int xx, int yy, float y, float cb, float cr)
{
    Uint8 R, G, B;
    float r, g, b;

    r = y + 1.402f * (cr - 128.0f);
    g = y - 0.344136f * (cb - 128.0f) - 0.714136f * (cr - 128.0f);
    b = y + 1.772f * (cb - 128.0f);

    R = (r > 255) ? 255 : r;
    G = (g > 255) ? 255 : g;
    B = (b > 255) ? 255 : b;

    R = (Uint8)(r < 0) ? 0 : r;
    G = (Uint8)(g < 0) ? 0 : g;
    B = (Uint8)(b < 0) ? 0 : b;

    setPixel(xx, yy, R, G, B);
}

YCbCr getYCbCr(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    YCbCr ycbcr;
    ycbcr.Y = 0 + (0.299 * kolor.r) + (0.587 * kolor.g) + (0.114 * kolor.b);
    ycbcr.Cb = 128 - (0.168736 * kolor.r) - (0.331264 * kolor.g) + (0.5 * kolor.b);
    ycbcr.Cr = 128 + (0.5 * kolor.r) - (0.418688 * kolor.g) - (0.081312 * kolor.b);

    return ycbcr;
}

void setHSL(int xx, int yy, float h, float s, float l)
{
    Uint8 R, G, B;
    float r, g, b, barwa, z1, z2, hh;

    hh = fmodf(h, 360.0f);
    if (hh < 0.0f)
        hh += 360.0f;

    if (s == 0.0f)
    {
        R = (Uint8)(l * 255.0f);
        G = (Uint8)(l * 255.0f);
        B = (Uint8)(l * 255.0f);
        setPixel(xx, yy, R, G, B);
        return;
    }

    if (l < 0.5f)
        z1 = l * (1.0f + s);
    else
        z1 = l + s - (l * s);

    z2 = 2.0f * l - z1;
    barwa = h / 360.0f;

    r = barwa + 0.333f;
    g = barwa;
    b = barwa - 0.333f;

    if (r < 0.0f) r += 1.0f;
    if (r > 1.0f) r -= 1.0f;
    if (g < 0.0f) g += 1.0f;
    if (g > 1.0f) g -= 1.0f;
    if (b < 0.0f) b += 1.0f;
    if (b > 1.0f) b -= 1.0f;

    if (6.0f * r < 1.0f)
        r = z2 + (z1 - z2) * 6.0f * r;
    else if (2.0f * r < 1.0f)
        r = z1;
    else if (3.0f * r < 2.0f)
        r = z2 + (z1 - z2) * (0.666f - r) * 6.0f;
    else
        r = z2;

    if (6.0f * g < 1.0f)
        g = z2 + (z1 - z2) * 6.0f * g;
    else if (2.0f * g < 1.0f)
        g = z1;
    else if (3.0f * g < 2.0f)
        g = z2 + (z1 - z2) * (0.666f - g) * 6.0f;
    else
        g = z2;

    if (6.0f * b < 1.0f)
        b = z2 + (z1 - z2) * 6.0f * b;
    else if (2.0f * b < 1.0f)
        b = z1;
    else if (3.0f * b < 2.0f)
        b = z2 + (z1 - z2) * (0.666f - b) * 6.0f;
    else
        b = z2;

    R = (Uint8)(r * 255.0f);
    G = (Uint8)(g * 255.0f);
    B = (Uint8)(b * 255.0f);

    setPixel(xx, yy, R, G, B);
}

HSL getHSL(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);
    HSL hsl;
    float R, G, B, min, max, delta;
    R = kolor.r / 255.0f;
    G = kolor.g / 255.0f;
    B = kolor.b / 255.0f;

    max = fmaxf(fmaxf(R, G), B);
    min = fminf(fminf(R, G), B);
    delta = max - min;
    hsl.L = (max + min) / 2.0f;

    if (delta == 0)
    {
        hsl.H = 0.0f;
        hsl.S = 0.0f;
    }
    else
    {
        hsl.S = (hsl.L < 0.5f) ? (max - min) / (max + min) : (max - min) / (2.0f - max - min);

        if (R == max)
            hsl.H = (G - B) / (max - min);
        else if (G == max)
            hsl.H = 2.0f + (B - R) / (max - min);
        else if (B == max)
            hsl.H = 4.0f + (R - G) / (max - min);

        hsl.H *= 60.0f;
    }

    return hsl;
}

//p2
void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    Uint16 rgb555 = ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);

    setRGB555(xx, yy, rgb555);
}

void setRGB555(int xx, int yy, Uint16 rgb555)
{
    Uint8 r = ((rgb555 >> 10) & 0x1F) << 3;
    Uint8 g = ((rgb555 >> 5) & 0x1F) << 3;
    Uint8 b = (rgb555 & 0x1F) << 3;

    setPixel(xx, yy, r, g, b);
}

void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    Uint16 rgb565 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

    setRGB565(xx, yy, rgb565);
}

void setRGB565(int xx, int yy, Uint16 rgb565)
{
    Uint8 r = ((rgb565 >> 11) & 0x1F) << 3;
    Uint8 g = ((rgb565 >> 5) & 0x3F) << 2;
    Uint8 b = (rgb565 & 0x1F) << 3;

    setPixel(xx, yy, r, g, b);
}

SDL_Color getRGB555(int xx, int yy)
{
    Uint16 data = getRGB555_(xx, yy);
    SDL_Color kolor;

    kolor.r = ((data >> 10) & 0x1F) << 3;
    kolor.g = ((data >> 5) & 0x1F) << 3;
    kolor.b = (data & 0x1F) << 3;

    return kolor;
}

Uint16 getRGB555_(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);

    return ((kolor.r >> 3) << 10 | ((kolor.g >> 3) << 5) | (kolor.b >> 3));
}

SDL_Color getRGB565(int xx, int yy)
{
    Uint16 data = getRGB565_(xx, yy);
    SDL_Color kolor;

    kolor.r = ((data >> 11) & 0x1F) << 3;
    kolor.g = ((data >> 5) & 0x3F) << 2;
    kolor.b = (data & 0x1F) << 3;

    return kolor;
}

Uint16 getRGB565_(int xx, int yy)
{
    SDL_Color kolor = getPixel(xx, yy);

    return ((kolor.r >>3) << 11 | ((kolor.g >> 2) << 5) | (kolor.b >> 3));
}

void podprobkowanieYUV(int xx, int yy, int x, int y)
{
    YUV p1, p2, p3, p4;
    float avgU, avgV;
    p1 = getYUV(xx, yy);
    p2 = getYUV(xx+1, yy);
    p3 = getYUV(xx, yy+1);
    p4 = getYUV(xx+1, yy+1);

    avgU = (p1.U + p2.U + p3.U + p4.U) / 4.0f;
    avgV = (p1.V + p2.V + p3.V + p4.V) / 4.0f;

    setYUV(x, y, p1.Y, avgU, avgV);
    setYUV(x+1, y, p2.Y, avgU, avgV);
    setYUV(x, y+1, p3.Y, avgU, avgV);
    setYUV(x+1, y+1, p4.Y, avgU, avgV);
}

void podprobkowanieYIQ(int xx, int yy, int x, int y)
{
    YIQ p1, p2, p3, p4;
    float avgI, avgQ;
    p1 = getYIQ(xx, yy);
    p2 = getYIQ(xx+1, yy);
    p3 = getYIQ(xx, yy+1);
    p4 = getYIQ(xx+1, yy+1);

    avgI = (p1.I + p2.I + p3.I + p4.I) / 4.0f;
    avgQ = (p1.Q + p2.Q + p3.Q + p4.Q) / 4.0f;

    setYIQ(x, y, p1.Y, avgI, avgQ);
    setYIQ(x+1, y, p2.Y, avgI, avgQ);
    setYIQ(x, y+1, p3.Y, avgI, avgQ);
    setYIQ(x+1, y+1, p4.Y, avgI, avgQ);
}

void podprobkowanieYCbCr(int xx, int yy, int x, int y)
{
    YCbCr p1, p2, p3, p4;
    float avgCb, avgCr;
    p1 = getYCbCr(xx, yy);
    p2 = getYCbCr(xx+1, yy);
    p3 = getYCbCr(xx, yy+1);
    p4 = getYCbCr(xx+1, yy+1);

    avgCb = (p1.Cb + p2.Cb + p3.Cb + p4.Cb) / 4.0f;
    avgCr = (p1.Cr + p2.Cr + p3.Cr + p4.Cr) / 4.0f;

    setYCbCr(x, y, p1.Y, avgCb, avgCr);
    setYCbCr(x+1, y, p2.Y, avgCb, avgCr);
    setYCbCr(x, y+1, p3.Y, avgCb, avgCr);
    setYCbCr(x+1, y+1, p4.Y, avgCb, avgCr);
}

void podprobkowanieH(int xx, int yy, int x, int y)
{
    HSL p1, p2, p3, p4;
    float avgH;
    p1 = getHSL(xx, yy);
    p2 = getHSL(xx+1, yy);
    p3 = getHSL(xx, yy+1);
    p4 = getHSL(xx+1, yy+1);

    avgH = (p1.H + p2.H + p3.H + p4.H) / 4.0f;

    setHSL(x, y, avgH, p1.S, p1.L);
    setHSL(x+1, y, avgH, p2.S, p2.L);
    setHSL(x, y+1, avgH, p3.S, p3.L);
    setHSL(x+1, y+1, avgH, p4.S, p4.L);
}

void podprobkowanieS(int xx, int yy, int x, int y)
{
    HSL p1, p2, p3, p4;
    float avgS;
    p1 = getHSL(xx, yy);
    p2 = getHSL(xx+1, yy);
    p3 = getHSL(xx, yy+1);
    p4 = getHSL(xx+1, yy+1);

    avgS = (p1.S + p2.S + p3.S + p4.S) / 4.0f;

    setHSL(x, y, p1.H, avgS, p1.L);
    setHSL(x+1, y, p2.H, avgS, p2.L);
    setHSL(x, y+1, p3.H, avgS, p3.L);
    setHSL(x+1, y+1, p4.H, avgS, p4.L);
}

void podprobkowanieL(int xx, int yy, int x, int y)
{
    HSL p1, p2, p3, p4;
    float avgL;
    p1 = getHSL(xx, yy);
    p2 = getHSL(xx+1, yy);
    p3 = getHSL(xx, yy+1);
    p4 = getHSL(xx+1, yy+1);

    avgL = (p1.L + p2.L + p3.L + p4.L) / 4.0f;

    setHSL(x, y, p1.H, p1.S, avgL);
    setHSL(x+1, y, p2.H, p2.S, avgL);
    setHSL(x, y+1, p3.H, p3.S, avgL);
    setHSL(x+1, y+1, p4.H, p4.S, avgL);
}

//p6
void ByteRunKompresja(int wejscie[], int dlugosc)
{
    int i = 0;
    while (i < dlugosc)
    {
        if ((i<dlugosc-1) && (wejscie[i] == wejscie[i+1]))
        {
            int j=0;
            while ((i+j<dlugosc-1) && (wejscie[i+j] == wejscie[i+1+j]) && (j<127))
                j++;
            cout<<"("<<-j<<"), "<<(int)wejscie[i+j]<<", ";
            i+=(j+1);
        }
        else
        {
            int j=0;
            while ((i+j <dlugosc-1) && (wejscie[i+j] != wejscie[i+j+1]) && (j<128))
                j++;
            if ((i+j == dlugosc-1) && (j<128))
                j++;
            cout<<"("<<(j-1)<<"), ";
            for (int k=0; k<j; k++)
                cout<<(int)wejscie[i+k]<<", ";
            i+=j;
        }
    }
}

void ByteRunDekompresja(int wejscie[], int dlugosc)
{
    //asd
}

void RLEKompresja(int wejscie[], int dlugosc)
{
    int i = 0;
    while (i < dlugosc)
    {
        if ((i<dlugosc-1) && (wejscie[i] == wejscie[i+1]))
        {
            int j=0;
            while ((i+j < dlugosc-1) && (wejscie[i+j] == wejscie[i+j+1]) && (j<254))
                j++;
            cout<<"("<<(j+1)<<"), "<<(int)wejscie[i+j]<<", ";
            i+=(j+1);
        }
        else
        {
            int j=0;
            while ((i+j < dlugosc-1) && (wejscie[i+j] != wejscie[i+j+1]) && (j<254))
                j++;
            if ((i+j == dlugosc-1) && (j<254))
                j++;
            cout<<(int) 0<<", "<<j<<", ";
            for (int k=0; k<j; k++)
                cout<<(int)wejscie[i+k]<<", ";
            if (j%2 != 0)
                cout<<(int) 0<<", ";
            i+=j;
        }
    }
}

void RLEDekompresja(int wejscie[], int dlugosc)
{
    //asd
}

/*
    //testy

    //test YCbCr
    for (int i=0; i<szerokosc/2; i++)
        for (int j=0; j<wysokosc/2; j++)
        {
            YCbCr ycbcr = getYCbCr(i, j);
            setYCbCr(i+szerokosc/2, j, ycbcr.Y, ycbcr.Cb, ycbcr.Cr);
        }

    //test hsl
    for (int i=0; i<szerokosc/2; i++)
        for (int j=0; j<wysokosc/2; j++)
        {
            HSL hsl = getHSL(i, j);
            setHSL(i, j+wysokosc/2, hsl.H, hsl.S, hsl.L);
        }

    //test yuv i yiq
    for (int i=0; i<szerokosc/2; i++)
        for (int j=0; j<wysokosc/2; j++)
        {
            YUV yuv = getYUV(i, j);
            YIQ yiq = getYIQ(i, j);
            setYUV(i+szerokosc/2, j, yuv.Y, yuv.U, yuv.V);
            setYIQ(i+szerokosc/2, j+wysokosc/2, yiq.Y, yiq.I, yiq.Q);
        }

    //test rgb555
    for (int i=0; i<szerokosc/2; i++)
        for (int j=0; j<wysokosc/2; j++)
        {
            SDL_Color rgb555 = getRGB555(i, j);
            Uint16 rgb555_ = getRGB555_(i, j);
            setRGB555(i+szerokosc/2, j, rgb555.r, rgb555.g, rgb555.b);
            setRGB555(i+szerokosc/2, j+wysokosc/2, rgb555_);
        }

    //test rgb565
    for (int i=0; i<szerokosc/2; i++)
        for (int j=0; j<wysokosc/2; j++)
        {
            SDL_Color rgb565 = getRGB565(i, j);
            Uint16 rgb565_ = getRGB565_(i, j);
            setRGB565(i+szerokosc/2, j, rgb565.r, rgb565.g, rgb565.b);
            setRGB565(i+szerokosc/2, j+wysokosc/2, rgb565_);
        }

    //podprobkowanie yuv, yiq, ycbcr
    for (int i=0; i<szerokosc; i+=2)
        for (int j=0; j<wysokosc; j+=2)
        {
            podprobkowanieYUV(i, j, i+szerokosc/2, j);
            podprobkowanieYIQ(i, j, i, j+wysokosc/2);
            podprobkowanieYCbCr(i, j, i+szerokosc/2, j+wysokosc/2);
        }

    //podprobkowanie hsl
    for (int i=0; i<szerokosc; i+=2)
        for (int j=0; j<wysokosc; j+=2)
        {
            podprobkowanieH(i, j, i+szerokosc/2, j);
            podprobkowanieS(i, j, i, j+wysokosc/2);
            podprobkowanieL(i, j, i+szerokosc/2, j+wysokosc/2);
        }
 */
