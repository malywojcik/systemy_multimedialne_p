#include "SM2025-Kompresje.h"
#include <iostream>
#include <cmath>
#include <map>
#include <string>

using namespace std;

static map<string, int> slownikMap;

vector<Uint8> ByteRunKompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int i = 0, dlugosc = wejscie.size();
    while (i < dlugosc)
    {
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1]))
        {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + 1 + j]) && (j < 127))
                j++;

            wyjscie.push_back((Uint8) (-(j)));
            wyjscie.push_back((Uint8) (-j));
            wyjscie.push_back(wejscie[i]);
            i += (j + 1);
        }
        else
        {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] != wejscie[i + j + 1]) && (j < 127))
                j++;
            wyjscie.push_back((Uint8) (j));
            for (int k = 0; k < j; k++)
                wyjscie.push_back(wejscie[i + k]);
            i += (j + 1);
        }
    }
    return wyjscie;
}

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

vector<Uint8> LZWKompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int i = 0, dlugosc = wejscie.size(), kod;

    LZWinicjalizacja();
    slowo aktualneSlowo = noweSlowo();

    if (dlugosc > 0)
    {
        aktualneSlowo = noweSlowo(wejscie[i++]);
        aktualneSlowo.kod = znajdzWSlowniku(aktualneSlowo);
        aktualneSlowo.wSlowniku = true;
    }

    while (i < dlugosc)
    {
        Uint8 znak = wejscie[i];
        slowo slowoZnak = polaczSlowo(aktualneSlowo, znak);
        kod = znajdzWSlowniku(slowoZnak);

        if (kod >= 0)
        {
            aktualneSlowo = slowoZnak;
            aktualneSlowo.kod = kod;
            aktualneSlowo.wSlowniku = true;
        }
        else
        {
            Uint16 wartosc = aktualneSlowo.kod;
            wyjscie.push_back(wartosc & 0xFF);
            wyjscie.push_back((wartosc >> 8) & 0xFF);

            dodajDoSlownika(slowoZnak);
            aktualneSlowo = noweSlowo(znak);
            aktualneSlowo.kod = znajdzWSlowniku(aktualneSlowo);
            aktualneSlowo.wSlowniku = true;
        }
        i++;
    }
    Uint16 wartosc = aktualneSlowo.kod;
    wyjscie.push_back(wartosc & 0xFF);
    wyjscie.push_back((wartosc >> 8) & 0xFF);

    return wyjscie;
}

vector<Uint8> ByteRunDekompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    int i = 0;
    while (i < wejscie.size())
    {
        int8_t n = (int8_t) wejscie[i];
        i++;
        if (n >= -127 && n <= -1)
        {
            int count = -n + 1;
            if (i < wejscie.size())
            {
                Uint8 val = wejscie[i];
                i++;
                for (int k = 0; k < count; k++)
                    wyjscie.push_back(val);
            }
        }
        else if (n >= 0 && n <= 127)
        {
            int count = n + 1;
            for (int k = 0; k < count; k++)
                if (i < wejscie.size())
                {
                    wyjscie.push_back(wejscie[i]);
                    i++;
                }
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

vector<Uint8> LZWDekompresja(const vector<Uint8> &wejscie)
{
    vector<Uint8> wyjscie;
    LZWinicjalizacja();

    int i = 0;
    if (i + 1 >= wejscie.size())
        return wyjscie;

    Uint16 kod = wejscie[i] | (wejscie[i + 1] << 8);
    i += 2;

    int staryKod = kod;
    if (kod < rozmiarSlownika)
        for (int k = 0; k < slownik[kod].dlugosc; k++)
            wyjscie.push_back(slownik[kod].element[k]);

    while (i + 1 < wejscie.size())
    {
        Uint16 nowyKod = wejscie[i] | (wejscie[i + 1] << 8);
        i += 2;

        int kodDoPrzetworzenia = nowyKod;
        slowo *slowoWejsciowe;

        if (kodDoPrzetworzenia >= rozmiarSlownika)
        {
            slowoWejsciowe = &slownik[staryKod];
            slowo tmp = *slowoWejsciowe;
            if (tmp.dlugosc < 4096)
            {
                tmp.element[tmp.dlugosc] = tmp.element[0];
                tmp.dlugosc++;
                for (int k = 0; k < tmp.dlugosc; k++)
                    wyjscie.push_back(tmp.element[k]);
                dodajDoSlownika(tmp);
            }
        }
        else
        {
            slowoWejsciowe = &slownik[kodDoPrzetworzenia];
            for (int k = 0; k < slowoWejsciowe->dlugosc; k++)
                wyjscie.push_back(slowoWejsciowe->element[k]);

            slowo tmp = slownik[staryKod];
            if (tmp.dlugosc < 4096)
            {
                tmp.element[tmp.dlugosc] = slowoWejsciowe->element[0];
                tmp.dlugosc++;
                dodajDoSlownika(tmp);
            }
        }
        staryKod = nowyKod;
    }
    return wyjscie;
}

void LZWinicjalizacja()
{
    slownikMap.clear();
    rozmiarSlownika = 0;
    for (int s = 0; s < 65536; s++)
    {
        slownik[s].kod = 0;
        slownik[s].dlugosc = 0;
        slownik[s].wSlowniku = false;
        memset(slownik[s].element, 0, sizeof(slownik[s].element));
    }
    slowo noweSlowo;
    for (int s = 0; s < 256; s++)
    {
        noweSlowo.dlugosc = 1;
        noweSlowo.element[0] = s;
        noweSlowo.kod = dodajDoSlownika(noweSlowo);
    }
}

int dodajDoSlownika(slowo nowy)
{
    if (rozmiarSlownika < 65536)
    {
        Uint16 nr = rozmiarSlownika;
        slownik[nr].kod = nr;
        slownik[nr].dlugosc = nowy.dlugosc;
        copy(begin(nowy.element), end(nowy.element), begin(slownik[nr].element));
        slownik[nr].wSlowniku = true;
        string klucz((char *) slownik[nr].element, slownik[nr].dlugosc);
        slownikMap[klucz] = nr;

        rozmiarSlownika++;
        return nr;
    }
    return -1;
}

slowo noweSlowo()
{
    slowo noweSlowo;
    noweSlowo.kod = 0;
    noweSlowo.dlugosc = 0;
    noweSlowo.wSlowniku = false;
    return noweSlowo;
}

slowo noweSlowo(Uint8 znak)
{
    slowo noweSlowo;
    noweSlowo.kod = 0;
    noweSlowo.dlugosc = 1;
    noweSlowo.element[0] = znak;
    noweSlowo.wSlowniku = false;
    return noweSlowo;
}

slowo polaczSlowo(slowo aktualneSlowo, Uint8 znak)
{
    slowo polaczoneSlowo;
    if (aktualneSlowo.dlugosc < 4096)
    {
        polaczoneSlowo.kod = 0;
        polaczoneSlowo.dlugosc = aktualneSlowo.dlugosc + 1;
        polaczoneSlowo.wSlowniku = false;

        for (int i = 0; i < aktualneSlowo.dlugosc; i++)
            polaczoneSlowo.element[i] = aktualneSlowo.element[i];
        polaczoneSlowo.element[aktualneSlowo.dlugosc] = znak;

        return polaczoneSlowo;
    }
    else
        return noweSlowo(znak);
}

int znajdzWSlowniku(slowo szukany)
{
    string klucz((char *) szukany.element, szukany.dlugosc);
    auto it = slownikMap.find(klucz);
    if (it != slownikMap.end())
        return it->second;

    return -1;
}

bool porownajSlowa(slowo slowo1, slowo slowo2)
{
    if (slowo1.dlugosc != slowo2.dlugosc)
        return false;
    for (int s = 0; s < slowo1.dlugosc; s++)
        if (slowo1.element[s] != slowo2.element[s])
            return false;

    return true;
}

Uint8 predyktorPaeth(Uint8 a, Uint8 b, Uint8 c)
{
    int p = (int) a + (int) b - (int) c;
    int pa = abs(p - (int) a);
    int pb = abs(p - (int) b);
    int pc = abs(p - (int) c);

    if (pa <= pb && pa <= pc)
        return a;
    else if (pb <= pc)
        return b;
    else
        return c;
}

void filtrPaeth(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp)
{
    int stride = szer * bpp;

    for (int y = 0; y < wys; y++)
        for (int x = 0; x < stride; x++)
        {
            int i = y * stride + x;
            Uint8 lewy = (x >= bpp) ? wejscie[i - bpp] : 0;
            Uint8 gora = (y > 0) ? wejscie[i - stride] : 0;
            Uint8 goraLewy = (x >= bpp && y > 0) ? wejscie[i - stride - bpp] : 0;
            wyjscie[i] = wejscie[i] - predyktorPaeth(lewy, gora, goraLewy);
        }
}

void defiltrPaeth(Uint8 *wejscie, Uint8 *wyjscie, int szer, int wys, int bpp)
{
    int stride = szer * bpp;

    for (int y = 0; y < wys; y++)
        for (int x = 0; x < stride; x++)
        {
            int i = y * stride + x;
            Uint8 lewy = (x >= bpp) ? wyjscie[i - bpp] : 0;
            Uint8 gora = (y > 0) ? wyjscie[i - stride] : 0;
            Uint8 goraLewy = (x >= bpp && y > 0) ? wyjscie[i - stride - bpp] : 0;
            wyjscie[i] = wejscie[i] + predyktorPaeth(lewy, gora, goraLewy);
        }
}
