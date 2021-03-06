// tablica4x4_v01_Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>
using namespace std;

#define L_WIERSZY 4
#define L_KOLUMN  4

void wprowadz_dane(int tab[][L_KOLUMN])
{
	int temp = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			cout << "Podaj wartosc [" << wiersze << "][" << kolumny << "]: ";
			cin >> temp;
			tab[wiersze][kolumny] = temp;
		}
	}
}

void wprowadz_dane_losowo(int tab[][L_KOLUMN])
{
	int temp = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			temp = rand();
			tab[wiersze][kolumny] = (temp % 100) + 1;
		}
	}
}

void wyswietl_dane(int tab[][L_KOLUMN])
{
	int temp = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			cout.width(4);
			cout << tab[wiersze][kolumny];
		}
		cout << endl;
	}
	cout << endl;
}

void wyswietl_dane_posortowane(int tab[])
{
	int temp = 0;
	for (int i = 0; i < (L_WIERSZY*L_KOLUMN); i++)
	{
		cout.width(4);
		cout << tab[i];
	}
	cout << endl;
}

float srednia(int tab[][L_KOLUMN])
{
	float suma = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			suma += tab[wiersze][kolumny];
		}
	}
	return (suma / (L_WIERSZY * L_KOLUMN));
}

int cmpfunc(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

float mediana(int tab[][L_KOLUMN], int tab_sort[])
{
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			tab_sort[wiersze*L_WIERSZY + kolumny] = tab[wiersze][kolumny];
		}
	}
	qsort(tab_sort, L_KOLUMN*L_WIERSZY, sizeof(tab_sort[0]), cmpfunc);
	return ((float)(tab_sort[(L_WIERSZY*L_KOLUMN - 1) / 2] + tab_sort[(L_WIERSZY*L_KOLUMN) / 2]) / 2);
}

void zapisz_dane(int tab[][L_KOLUMN])
{
	ofstream zapis("tablica.txt");
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			zapis.width(4);
			zapis << tab[wiersze][kolumny];
		}
		zapis << endl;
	}
	zapis.close();
}

void wczytaj_dane(int tab[][L_KOLUMN])
{
	int temp = 0;

	ifstream odczyt("tablica.txt");
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			odczyt >> temp;
			tab[wiersze][kolumny] = temp;
		}
	}
	odczyt.close();
}

void zamien_min_max(int tab[][L_KOLUMN])
{
	int w_min = tab[0][0], w_max = tab[0][0];

	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			if (tab[wiersze][kolumny] < w_min) w_min = tab[wiersze][kolumny];
			if (tab[wiersze][kolumny] > w_max) w_max = tab[wiersze][kolumny];
		}
	}

	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			if (tab[wiersze][kolumny] == w_min) tab[wiersze][kolumny] = w_max;
			else if (tab[wiersze][kolumny] == w_max) tab[wiersze][kolumny] = w_min;
		}
	}
}

void menu(void)
{
	cout << endl;
	cout << "1 - wprowadz dane" << endl;
	cout << "2 - wyswietl dane" << endl;
	cout << "3 - oblicz srednia i mediane" << endl;
	cout << "4 - zamien wartosc minimalna z maksymalna" << endl;
	cout << "5 - generuj dane losowo" << endl;
	cout << "z - zapisz dane do pliku" << endl;
	cout << "w - wczytaj dane z pliku" << endl;
	cout << "k - koniec programu" << endl;
	cout << endl;
}

int main()
{
	//typ_elementów_tablicy nazwa_tablicy[iloœæ wierszy][iloœæ kolumn];
	int tablica[L_WIERSZY][L_KOLUMN] = { 0 };
	int tab_sort_temp[L_WIERSZY*L_KOLUMN] = { 0 };
	char opcja = 0;

	while (opcja != 'k')
	{
		menu();
		opcja = _getch();
		_getch(); //dummy

		switch (opcja)
		{
		case '1':
			wprowadz_dane(tablica);
			break;

		case '2':
			wyswietl_dane(tablica);
			break;

		case '3':
			cout << "Srednia wartosci znajdujacych sie w tabeli wynosi: " << srednia(tablica) << endl;
			cout << "Mediana wartosci znajdujacych sie w tabeli wynosi: " << mediana(tablica, tab_sort_temp) << endl;
			break;

		case '4':
			zamien_min_max(tablica);
			cout << "Zamieniono wartosc minimalna z maksymalna." << endl;
			break;

		case '5':
			wprowadz_dane_losowo(tablica);
			cout << "Wygenerowano dane losowo." << endl;
			break;

		case 'z':
			zapisz_dane(tablica);
			cout << "Zapisano dane do pliku." << endl;
			break;

		case 'w':
			wczytaj_dane(tablica);
			cout << "Odczytano dane z pliku." << endl;
			break;

		case 'k':
			//zakonczenie programu
			break;

		default:
			cout << "Wybierz wlasciwa opcje." << endl << endl;
			break;
		}
	}

	return 0;
}
