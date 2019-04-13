#pragma once
#include <iostream>
#include <string>
#include "Ksiazki.h"
#include "Czytelnicy.h"
#include <string>
#include <fstream>

using namespace std;




void wyswietlMenu();
void wypozycz(Ksiazka* gl, Czytelnik* gc, const string nazw, const string imie, const string tytul);
void oddajKsiazke(Ksiazka* gl, Czytelnik* gc, const string nazw, const string imie, const string tytul);
void usunKs(Ksiazka*&gl, Czytelnik* gC, const string tytul);
bool sprCzyWypoz(Ksiazka* szukana, Czytelnik*gC);
Wypozyczona* znajdzWypozyczona(Ksiazka* szukana, Czytelnik*C);
