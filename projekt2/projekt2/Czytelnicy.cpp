#pragma once
#include "Czytelnicy.h"


void dodajCzytelnika(Czytelnik*&gl, const string nazw, const string im, const int nr)
{
	Czytelnik * nowy = new Czytelnik;
	nowy->nazwisko = nazw;
	nowy->imie = im;
	nowy->nr_karty = nr;
	nowy->lk = 0;
	nowy->Cnast = NULL;
	nowy->wypKs = NULL;

	if (gl == NULL) //jesli jest pusta dodajemy na poczatek
	{
		gl = nowy; return;
	}

	if (gl->nazwisko > nowy->nazwisko)
	{
		nowy->Cnast = gl;
		gl = nowy;
		return;
	}
	if (gl->nazwisko == nowy->nazwisko) //jesli nazwiska sie powtarzaja
	{
		if (gl->imie > nowy->imie) //porownujemy imiona
		{
			nowy->Cnast = gl;
			gl = nowy;
			return;
		}
	}
	Czytelnik * tmp = gl;
	while (tmp->Cnast != NULL && tmp->Cnast->nazwisko < nowy->nazwisko)
		tmp = tmp->Cnast;
	nowy->Cnast = tmp->Cnast;
	tmp->Cnast = nowy;
}



void zapiszC(Czytelnik*gC, fstream &plik) //zapisuje do pliku koncowy efekt listy czytelnikow
{
	while (gC != NULL)
	{
		plik << gC->nazwisko << " " << gC->imie << " " << gC->nr_karty << " " << gC->lk << endl; //czytelnicy
		Wypozyczona*wyp = gC->wypKs;
		while (wyp != NULL) {
			plik << wyp->wypozyczona->autor << " " << wyp->wypozyczona->tytul << endl;//ks wypozyczone
			wyp = wyp->nastWyp;
		}
		gC = gC->Cnast;
	}
}


bool wczytajC(fstream &plikC, const string n_plikuC, Czytelnik*&gC, Ksiazka*gK) //wczytuje z pliku do listy czytelnikow
{
	string imie, nazw, autor, tytul;
	int ileks, nr;
	plikC.open(n_plikuC);
	if (plikC.good())
	{
		while (!plikC.eof())
		{
			while (plikC >> nazw) {
				if (plikC >> imie) {
					if (plikC >> nr) {
						dodajCzytelnika(gC, nazw, imie, nr);
						if (plikC >> ileks) {
							if (ileks > 0) {
								for (int i = 0; i < ileks; ++i) {
									plikC >> autor;
									plikC >> tytul;
									Ksiazka*ks = znajdzKsiazke(gK, tytul);
									Czytelnik*czyt = znajdzCzytelnika(gC, nazw, imie);
									dodDoWypoz(czyt->wypKs, ks);
									(czyt->lk)++;  //zwiekszamy liczbe wypozyczonych ksiazek przez czytelnika
								}
							}
						}
					}
					else return false;
				}
				else return false;
			}

		}
		plikC.close(); return true;
	}
}



void wypiszC(Czytelnik* czyt) //wypisuje tylko jednego czytelnika i liste jego ksiazek
{
	if (czyt != NULL) {
		cout << czyt->nazwisko << " " << czyt->imie << " " << czyt->nr_karty << endl << "  Wypozyczonych ksiazek: " << czyt->lk << endl;
		if (czyt->wypKs != NULL)
			wypiszLW(czyt->wypKs);
	}
}

void wypiszLC(Czytelnik* glowa) //wypisuje liste wszystkich czytelnikow i ich ksiazek
{
	while (glowa != NULL)
	{
		wypiszC(glowa);
		glowa = glowa->Cnast;
	}
}

Czytelnik* znajdzCzytelnika(Czytelnik*gl, const string nazw, const string imie)
{
	while (gl != NULL)
	{
		if (gl->nazwisko == nazw && gl->imie == imie)
			return gl;
		gl = gl->Cnast;
	}
	return NULL; //jesli nie ma takiego czytelnika
}


void usunCzytelnika(Czytelnik* &gl, const string nazwisko, const string imie) //usuwa z listy czytelnikow
{
	Czytelnik*usun = znajdzCzytelnika(gl, nazwisko, imie);
	if (gl == NULL) { cout << "Brak czytelnikow w bazie!" << endl; return; }
	if (usun == NULL) { cout << "Nie ma takiego czytelnika w bazie!" << endl; return; }
	if (gl == usun)
	{
		if (usun->wypKs == NULL) //nie mozna usunac jesli lista wypozyczonych nie jest pusta
		{
			gl = gl->Cnast;
			delete usun; return;
		}
		cout << "Nie mozna usunac czytelnika!" << endl;
	}
	Czytelnik* tmp = gl;
	while ((tmp->Cnast != NULL) && tmp->Cnast != usun)
		tmp = tmp->Cnast;

	if (tmp->Cnast != NULL)
	{
		if (usun->wypKs == NULL) {
			usun = tmp->Cnast;
			tmp->Cnast = tmp->Cnast->Cnast;
			delete usun;
			return;
		}
		cout << "Nie mozna usunac czytelnika!" << endl;
	}
}



void usunLC(Czytelnik*&gl)
{
	while (gl != NULL)
	{
		Czytelnik*usun = gl;
		if (gl->wypKs != NULL)
			usunLW(gl->wypKs); //jesli ma wypozyczone ksiazki
		gl = gl->Cnast;
		delete usun;
	}
}