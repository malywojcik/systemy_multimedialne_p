#include "SM2025-Kompresje.h"

vector<Uint8> RLEKompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int dlugosc = wejscie.size();
    int i = 0;

    while (i < dlugosc)
    {
        if (i < dlugosc - 1 && wejscie[i] == wejscie[i + 1])
        {
            int runLength = 1;

            while (i + runLength < dlugosc && wejscie[i + runLength] == wejscie[i] && runLength < 255)
                runLength++;

            wyjscie.push_back((Uint8) runLength);
            wyjscie.push_back(wejscie[i]);

            i += runLength;
        }
        else
        {
            int litLength = 0;
            int tempIndex = i;

            while (tempIndex < dlugosc && litLength < 254)
            {
                if (tempIndex < dlugosc - 1 && wejscie[tempIndex] == wejscie[tempIndex + 1])
                    break;

                litLength++;
                tempIndex++;
            }

            wyjscie.push_back(0);
            wyjscie.push_back((Uint8) litLength);

            for (int k = 0; k < litLength; k++)
                wyjscie.push_back(wejscie[i + k]);

            if (litLength % 2 != 0)
                wyjscie.push_back(0);

            i += litLength;
        }
    }
    return wyjscie;
}

vector<Uint8> RLEDekompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int i = 0;
    int rozmiarWejscia = wejscie.size();

    while (i < rozmiarWejscia)
    {
        Uint8 n = wejscie[i++];

        if ((n > 0) && (i < rozmiarWejscia))
        {
            Uint8 val = wejscie[i++];
            for (int k = 0; k < n; k++)
                wyjscie.push_back(val);
        }
        else
        {
            if (i < rozmiarWejscia)
            {
                Uint8 count = wejscie[i++];

                for (int k = 0; k < count; k++)
                    if (i < rozmiarWejscia)
                        wyjscie.push_back(wejscie[i++]);


                if ((count % 2 != 0) && (i < rozmiarWejscia))
                    i++;
            }
        }
    }
    return wyjscie;
}

void filtrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp)
{
    int stride = szer * bpp;

    for (int y = 0; y < wys; y++)
        for (int x = 0; x < stride; x++)
        {
            int i = y * stride + x;
            Uint8 lewy = (x >= bpp) ? wejscie[i - bpp] : 0;
            Uint8 gora = (y > 0) ? wejscie[i - stride] : 0;
            wyjscie[i] = wejscie[i] - (((int) lewy + (int) gora) / 2);
        }
}

void defiltrAvg(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp)
{
    int stride = szer * bpp;

    for (int y = 0; y < wys; y++)
        for (int x = 0; x < stride; x++)
        {
            int i = y * stride + x;
            Uint8 lewy = (x >= bpp) ? wyjscie[i - bpp] : 0;
            Uint8 gora = (y > 0) ? wyjscie[i - stride] : 0;
            wyjscie[i] = wejscie[i] + (((int) lewy + (int) gora) / 2);
        }
}
