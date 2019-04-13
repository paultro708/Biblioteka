#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Ksiazka {
	string autor;
	string tytul;
	int liczba_egz;
	Ksiazka * Knast;
};

struct Wypozyczona {
	Ksiazka* wypozyczona;
	Wypozyczona* nastWyp;
};



bool wczytajKs(fstream &plikK, const string n_plikuK, Ksiazka*&glowaK);
void dodajKsiazke(Ksiazka*&gl, const string autor, const string tytul, const int le);
void dodDoWypoz(Wypozyczona*&gl, Ksiazka* doWyp);
void wypiszLK(Ksiazka* glowa);
void wypiszLW(Wypozyczona* glowa);
Ksiazka* znajdzKsiazke(Ksiazka*gl, const string tytul);
void usunZwyp(Wypozyczona *& gl, Wypozyczona*& usun);
void zapiszKs(Ksiazka* gK, fstream &plik);
void usunLW(Wypozyczona*&gl);
void usunLK(Ksiazka*&gl);