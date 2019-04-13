#pragma once
#include <iostream>
#include <string>
#include "Ksiazki.h"
#include <string>
#include <fstream>

using namespace std;

struct Czytelnik {
	string nazwisko;
	string imie;
	int nr_karty;
	int lk;
	Czytelnik * Cnast;
	Wypozyczona * wypKs;
};



bool wczytajC(fstream &plikC, const string n_plikuC, Czytelnik*&gC, Ksiazka*gK);
void dodajCzytelnika(Czytelnik*&gl, const string nazw, const string im, const int nr);
void wypiszC(Czytelnik* czyt);
void wypiszLC(Czytelnik* glowa);
Czytelnik* znajdzCzytelnika(Czytelnik*gl, const string nazw, const string imie);
void usunCzytelnika(Czytelnik* &gl, const string nazwisko, const string imie);
void zapiszC(Czytelnik*gC, fstream &plik);
void usunLC(Czytelnik*&gl);


