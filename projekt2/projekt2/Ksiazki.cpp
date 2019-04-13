#pragma once
#include "Ksiazki.h"

void dodajKsiazke(Ksiazka*&gl, const string autor, const string tytul, int const le)
{
	Ksiazka * nowa = new Ksiazka;
	nowa->autor = autor;
	nowa->tytul = tytul;
	nowa->liczba_egz = le;
	nowa->Knast = NULL;

	if (gl == NULL) //jesli jest pusta dodajemy na poczatek
	{
		gl = nowa; return;
	}
	if (gl->autor == nowa->autor && gl->tytul == nowa->tytul)//jesli dodajemy ta sama ksiazke
	{
		nowa->liczba_egz = (nowa->liczba_egz + gl->liczba_egz); gl = nowa; return; //dodajemy liczbe egzemplarzy
	}
	if (gl->tytul > nowa->tytul) //sortowanie wg tytulow
	{
		nowa->Knast = gl;
		gl = nowa;
		return;
	}
	Ksiazka * tmp = gl;
	while (tmp->Knast != NULL && tmp->Knast->tytul <= nowa->tytul)
		tmp = tmp->Knast;
	if (tmp->autor == nowa->autor && tmp->tytul == nowa->tytul)
	{
		tmp->liczba_egz = (nowa->liczba_egz + tmp->liczba_egz); nowa = tmp; return;
		//zwiekszamy liczbe dostepnych egzemplarzy jesli to ta sama ksiazka
	}
	nowa->Knast = tmp->Knast;
	tmp->Knast = nowa;
}


void dodDoWypoz(Wypozyczona*&gl, Ksiazka* doWyp) //dodaje do listy wypozyczonych u konkretnego czytelnika
{
	Wypozyczona * nowa = new Wypozyczona;
	nowa->wypozyczona = doWyp;
	nowa->nastWyp = NULL;
	if (doWyp != NULL) {
		if (gl == NULL) //jesli jest pusta dodajemy na poczatek
		{
			gl = nowa; return;
		}
		Wypozyczona* tmp = gl;
		while (tmp->nastWyp != NULL)
			tmp = tmp->nastWyp;
		tmp->nastWyp = nowa;
	}
}

void wypiszLK(Ksiazka* glowa) //wypisuje liste ksiazek
{
	while (glowa != NULL)
	{
		cout << glowa->autor << " " << '"' << glowa->tytul << '"' << " " << glowa->liczba_egz << endl;
		glowa = glowa->Knast;
	}
}

void wypiszLW(Wypozyczona* glowa) //wypisuje liste wypozyczonych ksiazek konkretnego czytelnika
{
	while (glowa != NULL)
	{
		Ksiazka* tmp = glowa->wypozyczona;
		if (tmp != NULL)
		{
			cout << tmp->autor << " " << '"' << tmp->tytul << '"' << " " << endl;
		}
		glowa = glowa->nastWyp;
	}
}


Ksiazka* znajdzKsiazke(Ksiazka*gl, const string tytul)
{
	while (gl != NULL)
	{
		if (gl->tytul == tytul)
			return gl;
		gl = gl->Knast;
	}
	return NULL;
}



void zapiszKs(Ksiazka* gK, fstream &plik) //zapisuje do pliku koncowy efekt listy ksiazek 
{
	while (gK != NULL)
	{
		plik << gK->autor << " " << gK->tytul << " " << gK->liczba_egz << endl;
		gK = gK->Knast;
	}
}

bool wczytajKs(fstream &plikK, const string n_plikuK, Ksiazka*&glowaK) //wczytuje z pliku do listy ksiazek
{
	string tytul, autor;
	int le;
	plikK.open(n_plikuK);
	if (plikK.good())
	{
		while (!plikK.eof())
		{
			while (plikK >> autor) {
				if (plikK >> tytul) {
					if (plikK >> le) {
						dodajKsiazke(glowaK, autor, tytul, le);
					}
					else return false;
				}
				else return false;
			}
		}
		plikK.close();
		return true; //jesli wszytko wczytalo sie poprawnie
	}
	else
	{
		plikK.close();
		return false;
	}
}

void usunLW(Wypozyczona*&gl)
{
	while (gl != NULL)
	{
		Wypozyczona*usun = gl;
		gl = gl->nastWyp;
		delete usun;
	}
}

void usunLK(Ksiazka*&gl)
{
	while (gl != NULL)
	{
		Ksiazka*usun = gl;
		gl = gl->Knast;
		delete usun;
	}
}

void usunZwyp(Wypozyczona *& gl, Wypozyczona*& usun) //usuwa z listy wypozyczonych
{
	if (gl == NULL) { return; }
	if (gl == usun)
	{
		gl = gl->nastWyp;
		delete usun; return;
	}
	Wypozyczona* tmp = gl;
	while ((tmp->nastWyp != NULL) && tmp->nastWyp != usun)
		tmp = tmp->nastWyp;

	if (tmp->nastWyp != NULL)
	{
		//usun = tmp->nastWyp;
		tmp->nastWyp = tmp->nastWyp->nastWyp;
		delete usun;
		return;
	}
}