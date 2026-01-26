// funkcje do operacji na plikach
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-MedianCut.h"
#include "SM2025-Pliki.h"

//gk
void zapiszPlik()
{
    SDL_Color k;  Uint16 w = szerokosc / 2, h = wysokosc / 2;  Uint8 bpp = 24;
    const char id[2] = {'D','G'};  std::ofstream f("obrazRGB.bin",std::ios::binary);
    f.write(id,2); f.write((char*)&w,2); f.write((char*)&h,2); f.put(bpp);
    for(int y=0;y<h;++y)for(int x=0;x<w;++x){ k=getPixel(x,y); f.write((char*)&k,3);}  f.close();
}

void odczytajPlik()
{
    SDL_Color k{}; Uint16 w,h; Uint8 bpp; char id[2]; std::ifstream f("obrazRGB.bin",std::ios::binary);
    if(!f) return; f.read(id,2); f.read((char*)&w,2); f.read((char*)&h,2); f.read((char*)&bpp,1);
    for(int y=0;y<h;++y)for(int x=0;x<w;++x){ f.read((char*)&k,3); setPixel(x,y,k.r,k.g,k.b);}  f.close();
}

static void pack8x5(const Uint8 idx[8], Uint8 out[5])
{
    for(int i=0;i<5;++i) out[i]=0;
    for(int i=0;i<8;++i){ int bit=i*5; int byte=bit>>3; int shift=bit&7;
        out[byte]|=idx[i]<<shift; out[byte+1]|=idx[i]>>(8-shift); }
}

static void unpack8x5(const Uint8 in[5], Uint8 idx[8])
{
    for(int i=0;i<8;++i){ int bit=i*5; int byte=bit>>3; int shift=bit&7;
        idx[i] = ((in[byte]>>shift)|(in[byte+1]<<(8-shift))) & 0x1F; }
}

void zapiszPlik5()
{
    const Uint16 w = 320, h = 200; Uint8 bpp = 5; const char id[2]={'D','G'};
    std::ofstream f("obraz5b.bin",std::ios::binary);
    f.write(id,2); f.write((char*)&w,2); f.write((char*)&h,2); f.put(bpp);
    Uint8 buf[8],packed[5];
    for(int y=0;y<h;++y)
        for(int x=0;x<w;x+=8){
            for(int i=0;i<8;++i){ SDL_Color k=getPixel(x+i,y); buf[i]=z24doK5b5(k);}  pack8x5(buf,packed); f.write((char*)packed,5);
        }
    f.close();
}

void odczytajPlik5()
{
    Uint16 w,h; Uint8 bpp; char id[2]; std::ifstream f("obraz5b.bin",std::ios::binary); if(!f) return;
    f.read(id,2); f.read((char*)&w,2); f.read((char*)&h,2); f.read((char*)&bpp,1);
    Uint8 packed[5],buf[8];
    for(int y=0;y<h;++y)
        for(int x=0;x<w;x+=8){ f.read((char*)packed,5); unpack8x5(packed,buf);
            for(int i=0;i<8;++i){ SDL_Color c=z5bKod24(buf[i]); setPixel(x+i,y,c.r,c.g,c.b);} }
    f.close();
}

void zapiszPlik5blok()
{
    const Uint16 w = 320, h = 200; Uint8 bpp = 5; const char id[2]={'D','G'};
    std::ofstream f("obraz5b_blok.bin",std::ios::binary);
    f.write(id,2); f.write((char*)&w,2); f.write((char*)&h,2); f.put(bpp);
    Uint8 buf[8],packed[5];
    for(int xb=0;xb<w;xb+=8)
        for(int y=0;y<h;++y){
            for(int i=0;i<8;++i){ SDL_Color k=getPixel(xb+i,y); buf[i]=z24doK5b5(k);} pack8x5(buf,packed); f.write((char*)packed,5);
        }
    f.close();
}

void odczytajPlik5blok()
{
    Uint16 w,h; Uint8 bpp; char id[2]; std::ifstream f("obraz5b_blok.bin",std::ios::binary); if(!f) return;
    f.read(id,2); f.read((char*)&w,2); f.read((char*)&h,2); f.read((char*)&bpp,1);
    Uint8 packed[5],buf[8];
    for(int xb=0;xb<w;xb+=8)
        for(int y=0;y<h;++y){ f.read((char*)packed,5); unpack8x5(packed,buf);
            for(int i=0;i<8;++i){ SDL_Color c=z5bKod24(buf[i]); setPixel(xb+i,y,c.r,c.g,c.b);} }
    f.close();
}
