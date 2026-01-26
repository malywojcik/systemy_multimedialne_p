// metody do algorytmu kwantyzacji (MedianCut)
#include "SM2025-MedianCut.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"

//gk
void sortujKubekBW(int s,int k)
{
    for(int p=s;p<=k;++p)
    {
        int m=p;for(int i=p;i<=k;++i)
        if(obrazekS[i]<obrazekS[m])
            m=i;
        swap(obrazekS[p],obrazekS[m]);
        swap(obrazekK[p],obrazekK[m]);
    }
}

int znajdzSasiadaBW(Uint8 v)
{
    int best=999, id=0;
    for(int i=0;i<32;++i)
    {
        int d=abs(int(v)-int(paleta5s[i].r));
        if(d<best)
                best=d;id=i;

    }
    return id;
}

int znajdzSasiad(SDL_Color c)
{
    float best=1e9; int id=0;
    for(int i=0;i<32;++i)
    { SDL_Color p=paleta5k[i]; float d=(c.r-p.r)*(c.r-p.r)+(c.g-p.g)*(c.g-p.g)+(c.b-p.b)*(c.b-p.b); if(d<best){best=d;id=i;}} return id;
}

Uint8 najwiekszaRoznica(int s,int k)
{
    Uint8 minR=255,maxR=0,minG=255,maxG=0,minB=255,maxB=0;
    for(int i=s;i<=k;++i){SDL_Color c=obrazekK[i]; if(c.r<minR)minR=c.r; if(c.r>maxR)maxR=c.r; if(c.g<minG)minG=c.g; if(c.g>maxG)maxG=c.g; if(c.b<minB)minB=c.b; if(c.b>maxB)maxB=c.b;}
    int dR=maxR-minR,dG=maxG-minG,dB=maxB-minB; int m=max({dR,dG,dB}); return (m==dR)?1:(m==dG?2:3);
}

void sortujKubek(int s,int k,Uint8 comp)
{
    for(int p=s;p<=k;++p){int m=p;for(int i=p;i<=k;++i){bool c=false; switch(comp){case 1:c=obrazekK[i].r<obrazekK[m].r;break;case 2:c=obrazekK[i].g<obrazekK[m].g;break;case 3:c=obrazekK[i].b<obrazekK[m].b;break;} if(c)m=i;} swap(obrazekK[p],obrazekK[m]);}
}


void MedianCutBW(int s,int k,int depth)
{
    if(depth>0){ sortujKubekBW(s,k); int mid=(s+k+1)/2; MedianCutBW(s,mid-1,depth-1); MedianCutBW(mid,k,depth-1);} else {
        long sum=0; for(int i=s;i<=k;++i) sum+=obrazekS[i]; Uint8 g=sum/(k+1-s); paleta5s[ileKubelkow++]={g,g,g,255}; }
}


void MedianCut(int s,int k,int depth)
{
    if(depth>0){Uint8 c=najwiekszaRoznica(s,k); sortujKubek(s,k,c); int mid=(s+k+1)/2; MedianCut(s,mid-1,depth-1); MedianCut(mid,k,depth-1);} else {
        long r=0,g=0,b=0; for(int i=s;i<=k;++i){r+=obrazekK[i].r; g+=obrazekK[i].g; b+=obrazekK[i].b;} int n=k+1-s; paleta5k[ileKubelkow++]={(Uint8)(r/n),(Uint8)(g/n),(Uint8)(b/n),255}; }
}


void paletaMedianCutBW()
{
    ileKubelkow=0; czyscPalete(); int n=0; for(int y=0;y<200;++y)for(int x=0;x<320;++x){SDL_Color c=getPixel(x,y); Uint8 g=Uint8(0.299*c.r+0.587*c.g+0.114*c.b); obrazekS[n]=g; obrazekK[n]=c; ++n;}
    MedianCutBW(0,n-1,5);
    /* rozciągnięcie 0‑255 → pełny kontrast */
    Uint8 mn=255,mx=0; for(int i=0;i<32;++i){if(paleta5s[i].r<mn)mn=paleta5s[i].r; if(paleta5s[i].r>mx)mx=paleta5s[i].r;}
    if(mx==mn) mx=mn+1;
    for(int i=0;i<32;++i){Uint8 g=paleta5s[i].r; Uint8 gs=Uint8((int(g)-mn)*255/(mx-mn)); paleta5s[i]={gs,gs,gs,255};}
    for(int y=0;y<200;++y)for(int x=0;x<320;++x){Uint8 g=getPixel(x,y).r; int idx=znajdzSasiadaBW(g); SDL_Color c=paleta5s[idx]; setPixel(x+320,y+200,c.r,c.g,c.b);}
    narysujPalete(0,200,paleta5s); SDL_UpdateWindowSurface(window);
}

void paletaMedianCut()
{
    ileKubelkow=0; czyscPalete(); int n=0; for(int y=0;y<200;++y)for(int x=0;x<320;++x){SDL_Color c=getPixel(x,y); obrazekK[n++]=c;}
    MedianCut(0,n-1,5);
    for(int y=0;y<200;++y)for(int x=0;x<320;++x){SDL_Color c=getPixel(x,y); int idx=znajdzSasiad(c); SDL_Color p=paleta5k[idx]; setPixel(x+320,y+200,p.r,p.g,p.b);}
    narysujPalete(0,200,paleta5k); SDL_UpdateWindowSurface(window);
}

using namespace std;
