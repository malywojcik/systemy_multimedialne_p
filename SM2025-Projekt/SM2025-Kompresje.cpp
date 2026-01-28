#include "SM2025-Kompresje.h"

vector<Uint8> RLEKompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int i = 0, dlugosc = wejscie.size();
    while (i < dlugosc)
    {
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1]))
        {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + j + 1]) && (j < 254))
                j++;
            wyjscie.push_back((Uint8) (j + 1));
            wyjscie.push_back(wejscie[i]);
            i += (j + 1);
        }
        else
        {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] != wejscie[i + j + 1]) && (j < 254))
                j++;
            if ((i + j == dlugosc - 1) && (j < 254))
                j++;
            int count = j + 1;
            wyjscie.push_back(0);
            wyjscie.push_back(count);
            for (int k = 0; k < count; k++)
                wyjscie.push_back(wejscie[i + k]);
            if (count % 2 != 0)
                wyjscie.push_back(0);
            i += count;
        }
    }
    return wyjscie;
}

vector<Uint8> RLEDekompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int i = 0;
    while (i < wejscie.size())
    {
        Uint8 n = wejscie[i++];
        if (n > 0)
            if (i < wejscie.size())
            {
                Uint8 val = wejscie[i++];
                for (int k = 0; k < n; k++)
                    wyjscie.push_back(val);
            }

        else
            if (i < wejscie.size())
            {
                Uint8 count = wejscie[i++];
                for (int k = 0; k < count; k++)
                    if (i < wejscie.size())
                        wyjscie.push_back(wejscie[i++]);

                if (count % 2 != 0)
                    i++;
            }
    }
    return wyjscie;
}

void filtrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp)
{
    int stride = szer * bpp;

    for (int y =0; y<wys; y++)
        for (int x=0; x< stride; x++)
        {
            int i = y* stride + x;
            Uint8 lewy = (x >= bpp) ? wejscie[i - bpp] : 0;
            Uint8 gora = (y > 0) ? wejscie[i - stride] : 0;
            wyjscie[i] = wejscie[i] - (((int)lewy + (int)gora) / 2);
        }
}

void defiltrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp)
{
    int stride = szer * bpp;

    for (int y =0; y<wys; y++)
        for (int x=0; x< stride; x++)
        {
            int i = y* stride + x;
            Uint8 lewy = (x >= bpp) ? wyjscie[i - bpp] : 0;
            Uint8 gora = (y > 0) ? wyjscie[i - stride] : 0;
            wyjscie[i] = wejscie[i] + (((int)lewy + (int)gora) / 2);
        }
}
