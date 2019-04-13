#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <numeric>
#include "Czytelnicy.h"
#include "Ksiazki.h"
#include "Obsluga_Uzytkownika.h"

using namespace std;



int main()
{
	Czytelnik* glowaC = NULL;
	Ksiazka* glowaK = NULL;
	
	string n_plikuK,n_plikuC;
	char wybor;

	fstream plikK,plikC;
	cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane do listy ksiazek"<<endl<<"lub utworzyc plik o tej nazwie z nowa baza ksiazek: ";
	cin >> n_plikuK;
	cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane do listy czytelnikow"<<endl<<"lub utworzyc plik o tej nazwie z nowa baza czytelnikow: ";
	cin >> n_plikuC;
	
	bool ks =wczytajKs(plikK, n_plikuK, glowaK);
	bool c=wczytajC(plikC, n_plikuC,glowaC,glowaK);
	if (ks && c)
		cout << "Udalo sie poprawnie wczytac dane z plikow. Mozesz rozpoczac prace! " << endl;
	else cout << "Nie udalo sie poprawnie wczytac plikow! Utworz nowa baze! " << endl;
	
	string imie, nazwisko, tytul, autor, lE;
	int le;
	do {
		wyswietlMenu();
		cin >> wybor;
		switch (wybor)
		{
		case '1':
			cout << "Podaj nazwisko czytelnika: " << endl;
			cin >> nazwisko;
			cout << "Podaj imie czytelnika: " << endl;
			cin >> imie;
			cout << "Podaj nr karty: ";
			cin >> le;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits < streamsize >::max(), '\n');
				cout << "Podaj wlasciwy nr karty: ";
				cin >> le;
			}
			dodajCzytelnika(glowaC, nazwisko, imie, le);
			break;
		case '2':
			cout << "Podaj autora w formacie Nazwisko_Imie: " << endl;
			cin >> autor;
			cout << "Podaj tytul ksiazki w formacie slowo1_slowo2: " << endl;
			cin >> tytul;
			cout << "Wprowadz liczbe egzemplrzy: " << endl;
			cin >> le; 
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits < streamsize >::max(), '\n');
				cout << "Wprowadz wlasciwa liczbe: ";
				cin >> le;
			}
			dodajKsiazke(glowaK, autor, tytul, le);
			break;
		case '3':
			cout << "Podaj nazwisko czytelnika: " << endl;
			cin >> nazwisko;
			cout << "Podaj imie czytelnika: " << endl;
			cin >> imie;
			usunCzytelnika(glowaC, nazwisko, imie);
			break;
		case '4':
			cout << "Podaj tytul ksiazki w formacie slowo1_slowo2: " << endl;
			cin >> tytul;
			usunKs(glowaK, glowaC, tytul);
			break;
		case '5':
			cout << "Podaj nazwisko czytelnika: " << endl;
			cin >> nazwisko;
			cout << "Podaj imie czytelnika: " << endl;
			cin >> imie;
			cout << "Podaj tytul ksiazki w formacie slowo1_slowo2: " << endl;
			cin >> tytul;
			wypozycz(glowaK, glowaC, nazwisko, imie, tytul);
			break;
		case '6':
			cout << "Podaj nazwisko czytelnika: " << endl;
			cin >> nazwisko;
			cout << "Podaj imie czytelnika: " << endl;
			cin >> imie;
			cout << "Podaj tytul ksiazki w formacie slowo1_slowo2: " << endl;
			cin >> tytul;
			oddajKsiazke(glowaK, glowaC, nazwisko, imie, tytul);
			break;
		case '7':
			wypiszLC(glowaC);
			break;
		case '8':
			wypiszLK(glowaK);
			break;
		case '9':
			plikK.open(n_plikuK, ios::out);zapiszKs(glowaK, plikK);plikK.close();
			plikC.open(n_plikuC, ios::out);	zapiszC(glowaC, plikC);plikC.close();
			usunLC(glowaC);
			usunLK(glowaK);
			_CrtDumpMemoryLeaks();
			return 0;
			break;
		default: cout << "Wprowadz dostepna opcje! " << endl;
			break;
		}
	} while (wybor != '9');
	return 0;
}

