#pragma once
#include "Obsluga_Uzytkownika.h"


Wypozyczona* znajdzWypozyczona(Ksiazka* szukana, Czytelnik*C) //szuka danej ksiazki w liscie wypozyczonych czytelnika
{
	if (C != NULL)
	{
		Wypozyczona* tmp = C->wypKs;
		while (tmp != NULL)
		{
			if (tmp->wypozyczona == szukana)
				return tmp;
			tmp = tmp->nastWyp;
		}
	}
	return NULL;
}

bool sprCzyWypoz(Ksiazka* szukana, Czytelnik*gC) //spr czy dana ksiazka jest przez kogos wypozyczona
{
	while (gC != NULL)
	{
		if (znajdzWypozyczona(szukana, gC) == NULL)
			gC = gC->Cnast;
		else return true; //jest wypozyczona
	}
	return false;
}

void usunKs(Ksiazka*&gl, Czytelnik*gC, const string tytul) //usuwa ksiazke z listy
{
	Ksiazka*usun = znajdzKsiazke(gl, tytul);
	if (gl == NULL) { cout << "Brak ksiazek w bazie!" << endl; return; }
	if (usun == NULL) { cout << "Nie ma takiej ksiazki w bazie!" << endl; return; }
	if (sprCzyWypoz(usun, gC) == false) {
		if (gl == usun) //jesli jest to pierwszy element
		{
			gl = gl->Knast;
			delete usun; return;
		}
		Ksiazka* tmp = gl;
		while ((tmp->Knast != NULL) && tmp->Knast != usun)
			tmp = tmp->Knast;

		if (tmp->Knast != NULL)
		{
			usun = tmp->Knast;
			tmp->Knast = tmp->Knast->Knast;
			delete usun;
			return;
		}
	}
	else cout << "Ksiazka jest wypozyczona!" << endl;
}

void wypozycz(Ksiazka* gl, Czytelnik* gc, const string nazw, const string imie, const string tytul) //dodaje do listy wypozyczonych czytelnika
{
	Ksiazka*szukana = znajdzKsiazke(gl, tytul);
	if (szukana == NULL)
	{
		cout << "Brak ksiazki w systemie!" << endl; return;
	}
	if (szukana->liczba_egz == 0) //jesli jest w bazie, spr jest wystarczajaca ilosc
	{
		cout << "Brak dostepnych egzemplarzy!" << endl; return;
	}
	Czytelnik*czytel = znajdzCzytelnika(gc, nazw, imie); //szuka czytelnika, ktory chce wypozyczyc dana ksiazke
	if (czytel == NULL)
	{
		cout << "Nie ma takiego czytelnika w bazie!" << endl; return;
	}

	dodDoWypoz(czytel->wypKs, szukana); //dodajemy do listy wypozyczonych ksiazek czytelnika
	szukana->liczba_egz = (szukana->liczba_egz - 1); //dekrementujemy liczbe dostepnych egzemparzy
	(czytel->lk)++;  //zwiekszamy liczbe wypozyczonych ksiazek przez czytelnika
}



void oddajKsiazke(Ksiazka* gl, Czytelnik* gc, const string nazw, const string imie, const string tytul)
{
	Czytelnik* czyt = znajdzCzytelnika(gc, nazw, imie);
	if (czyt == NULL)
	{
		cout << "Nie ma takiego czytelnika w bazie!" << endl; return;
	}
	Ksiazka* ks = znajdzKsiazke(gl, tytul);
	Wypozyczona* wyp = znajdzWypozyczona(ks, czyt); //w liscie wypozyczonych czytelnika
	if (ks == NULL) {
		cout << "Brak takiej ksiazki w bazie!" << endl; return;
	}
	if (wyp == NULL)
	{
		cout << "Nie znaleziono takiej ksiazki u czytelnika!" << endl;
		return;
	}
	usunZwyp(czyt->wypKs, wyp); //usuwamy ksiazke z listy wypozyczonych u czytelnika
	(ks->liczba_egz)++; //zwiekszamy liczbe dostepnych egzemlarzy
	(czyt->lk)--;  //dekrementujemy liczbe wypozyczonych ksiazek przez czytelnika
}


void wyswietlMenu()
{
	cout << "====" << endl;
	cout << "MENU" << endl << "Wybierz jedna opcje:" << endl;
	cout << "1. Dodaj czytelnika" << endl;
	cout << "2. Dodaj ksiazke" << endl;
	cout << "3. Usun czytelnika" << endl;
	cout << "4. Usun ksiazke" << endl;
	cout << "5. Wypozycz ksiazke" << endl;
	cout << "6. Oddaj ksiazke" << endl;
	cout << "7. Wyswietl liste czytelnikow i ich ksiazek" << endl;
	cout << "8. Wyswietl liste ksiazek" << endl;
	cout << "9. Wyjscie" << endl;
	cout << "Wybieram: ";
}

