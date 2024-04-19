#pragma once
#include <iostream> // cin, cout
#include <string> // string
#include <locale.h> // setlocale(LC_CTYPE, "Polish");
#include <vector> // vector
#include <conio.h> // _getch();

using namespace std;

class Gosc {
private:
	string _imie;
	string _nazwisko;
	int _wiek;

public:
	Gosc(string imie, string nazwisko, int wiek);

	string get_imie();
	string get_nazwisko();
	int get_wiek();
};

class Pokoj {
private:
	int _id;
	int _typ_pokoju;

public:
	Pokoj(int id, int typ_pokoju);

	int get_id();
	int get_typ_pokoju();
};

class Rezerwacja {
private:
	int _id;
	Gosc* _gosc;
	Pokoj* _pokoj;
	tm _data_poczatek;
	tm _data_koniec;

public:
	Rezerwacja(int id, Gosc* gosc, Pokoj* pokoj, tm data_poczatek, tm data_koniec);

	int get_id();
	void set_id(int id);
	Gosc* get_gosc();
	Pokoj* get_pokoj();
	tm get_data_poczatek();
	tm get_data_koniec();
};


class Hotel {
private:
	string _nazwa;
	vector<Gosc*> goscie; //kontener z goœæmi w hotelu
	vector<Rezerwacja*> rezerwacje; //kontener z rezerwacjami

public:
	string get_nazwa();
	vector<Pokoj*> pokoje; // kontener z pokojami w hotelu


	Hotel(string nazwa);

	void dodaj_goscia(Gosc* gosc);
	void lista_gosci();

	void dodaj_pokoj(Pokoj* pokoj);
	Pokoj* znajdz_pokoj(int numer_pokoju);
	void informacje_o_pokoju(Pokoj* pokoj);
	void lista_pokoi();

	Rezerwacja* znajdz_rezerwacje(int numer_rezerwacji);
	void dodaj_rezerwacje();
	void zobacz_rezerwacje(int numer_rezerwacji);
	void anuluj_rezerwacje(int numer_rezerwacji);
	void lista_rezerwacji();

	int licz_dni(int numer_rezerwacji);
	int ilosc_osob(int numer_rezerwacji);

	bool czy_dostepny(int numer_pokoju, tm data);
	bool czy_dostepny_w_przedziale(int numer_pokoju, tm data_od, tm data_do);
};


int menu();
void usun_linie();
int miesiace(int miesiac, int rok);
void pokaz_date(tm data);
void pokaz_przedzial(tm data_od, tm data_do);
tm pobierz_date();
bool data_w_przedziale(tm data_od, tm data_do, tm data);
bool kolejnosc_przedzialu(tm data_od, tm data_do);
bool dlugosc_przedzialu(tm data_od, tm data_do);