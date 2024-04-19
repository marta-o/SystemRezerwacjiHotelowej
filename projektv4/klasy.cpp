#include "klasy.h"

//funkcja z menu pocz¹tkowym
int menu() {
	int wybor;
	cout << "	MENU	" << endl;
	cout << "--------------------" << endl;
	cout << "1. Dodaj rezerwacje" << endl;
	cout << "2. Szukaj rezerwacji " << endl;
	cout << "3. Anuluj rezerwacje" << endl;
	cout << "4. Informacje o pokoju" << endl;
	cout << "5. Poka¿ listê pokoi" << endl;
	cout << "6. Poka¿ listê goœci" << endl;
	cout << "7. Poka¿ listê rezerwacji" << endl;
	cout << "8. Kwota ca³kowita za rezerwacjê" << endl;
	cout << "9. SprawdŸ czy dany pokój jest dostêpny" << endl;
	cout << "10. Poka¿ dostêpne pokoje" << endl;
	cout << "11. Poka¿ zarezerwowane pokoje" << endl;
	cout << "12. Zakoñcz" << endl;
	cout << "--------------" << endl;
	cout << "Wybierz opcje: ";
	cin >> wybor;
	while (cin.fail()) {
		usun_linie();
		cout << "Nie ma takiej opcji. Wybierz jeszcze raz:  ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> wybor;
	}
	return wybor;
}

//konstruktor klasy Gosc
Gosc::Gosc(string imie, string nazwisko, int wiek) : _imie(imie), _nazwisko(nazwisko), _wiek(wiek) {}

//gettery klasy Gosc
string Gosc::get_imie() {
	return _imie;
}

string Gosc::get_nazwisko() {
	return _nazwisko;
}

int Gosc::get_wiek() {
	return _wiek;
}

//konstruktor klasy Pokoj
Pokoj::Pokoj(int id, int typ_pokoju) : _id(id), _typ_pokoju(typ_pokoju) {}

//gettery klasy Pokoj
int Pokoj::get_id() {
	return _id;
}

int Pokoj::get_typ_pokoju() {
	return _typ_pokoju;
}

//konstruktor klasy Rezerwacja
Rezerwacja::Rezerwacja(int id, Gosc* gosc, Pokoj* pokoj, tm data_poczatek, tm data_koniec) : _id(id), _gosc(gosc), _pokoj(pokoj), _data_poczatek(data_poczatek), _data_koniec(data_koniec) {}

//gettery i setter klasy Rezerwacja
int Rezerwacja::get_id() {
	return _id;
}

void Rezerwacja::set_id(int id) {
	_id = id;
}

Gosc* Rezerwacja::get_gosc() {
	return _gosc;
}

Pokoj* Rezerwacja::get_pokoj() {
	return _pokoj;
}

tm Rezerwacja::get_data_poczatek() {
	return _data_poczatek;
}

tm Rezerwacja::get_data_koniec() {
	return _data_koniec;
}

//konstruktor klasy Hotel
Hotel::Hotel(string nazwa) : _nazwa(nazwa) {}

string Hotel::get_nazwa() {
	return _nazwa;
}

//funkcja dodaj¹ca goœcia do kontenera
void Hotel::dodaj_goscia(Gosc* gosc) {
	goscie.push_back(gosc);
}

//funkcja wypisuj¹ca listê goœci
void Hotel::lista_gosci() {
	if (goscie.begin() == goscie.end()) {
		cout << "Brak goœci." << endl;
	}
	else {
		for (auto i = goscie.begin(); i != goscie.end(); i++) {
			cout << (*i)->get_imie() << " " << (*i)->get_nazwisko() << ", wiek: " << (*i)->get_wiek() << endl;
		}
	}
}

//funkcja dodaj¹ca pokój do kontenera
void Hotel::dodaj_pokoj(Pokoj* pokoj) {
	pokoje.push_back(pokoj);
}

//funkcja znajduj¹ca pokój o podanym numerze
Pokoj* Hotel::znajdz_pokoj(int numer_pokoju) {
	for (auto i = pokoje.begin(); i != pokoje.end(); i++) {
		if ((*i)->get_id() == numer_pokoju) {
			return (*i);
		}
	}
	return nullptr;
}

//funkcja wypisuj¹ca dane wybranego pokoju
void Hotel::informacje_o_pokoju(Pokoj* pokoj) {
	if (pokoj == nullptr) {
		cout << "Nie ma takiego pokoju.";
	}
	else {
		cout << "Pokój numer " << pokoj->get_id() << ", ";
		cout << "typ pokoju: ";
		if (pokoj->get_typ_pokoju() == 1) {
			cout << "jednoosobowy";
		}
		else if (pokoj->get_typ_pokoju() == 2) {
			cout << "dwuosobowy";
		}
		else if (pokoj->get_typ_pokoju() == 3) {
			cout << "trzyosobowy";
		}
		else if (pokoj->get_typ_pokoju() == 4) {
			cout << "czteroosobowy";
		}
	}
	cout << endl;
}

void Hotel::lista_pokoi() {
	if (pokoje.begin() == pokoje.end()) {
		cout << "Brak pokoi." << endl;
	}
	else {
		for (auto i = pokoje.begin(); i != pokoje.end(); i++) {
			informacje_o_pokoju(*i);
		}
	}
}

//funkcja szukaj¹ca rezerwacji o podanym numerze
Rezerwacja* Hotel::znajdz_rezerwacje(int numer_rezerwacji) {
	for (auto i = rezerwacje.begin(); i != rezerwacje.end(); i++) {
		if ((*i)->get_id() == numer_rezerwacji) {
			return (*i);
		}
	}
	return nullptr;
}

//funkcja dodaj¹ca rezerwacje z pobranymi danymi od u¿ytkownika
void Hotel::dodaj_rezerwacje() {
	tm data_od{}, data_do{};
	string imie{}, nazwisko{};
	int wiek{};
	int numer_pokoju{};

	//pobieranie dat pobytu od u¿ytkownika
	cout << "Data przyjazdu:" << endl;
	data_od = pobierz_date();
	cout << "Data wyjazdu: " << endl;
	data_do = pobierz_date();
	//zabezpiecznie by daty by³y chronologicznie oraz by pobyt nie by³ d³u¿szy ni¿ 2 miesi¹ce
	while (kolejnosc_przedzialu(data_od, data_do) == false || dlugosc_przedzialu(data_od, data_do) == false) {
		for (int i = 0; i < 8; i++) {
			usun_linie();
		}
		cout << "Nie mo¿na stworzyæ takiej rezerwacji" << endl;
		cout << "Data przyjazdu:" << endl;
		data_od = pobierz_date();
		cout << "Data wyjazdu: " << endl;
		data_do = pobierz_date();
	}
	//wypisanie dat
	pokaz_przedzial(data_od, data_do);

	//pobranie numeru pokoju od uzytkownika
	cout << "Numer pokoju: ";
	cin >> numer_pokoju;
	//zabezpiecznie by nie wpisaæ nieistniej¹cego pokoju
	while (cin.fail() || znajdz_pokoj(numer_pokoju) == nullptr) {
		usun_linie();
		cout << "Nie ma takiego pokoju: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> numer_pokoju;
		//sprawdzenie czy pokój jest dostêpny w podanym terminie
		while (czy_dostepny_w_przedziale(numer_pokoju, data_od, data_do) == false) {
			usun_linie();
			cout << "Pokój niedostêpny. Podaj inny pokój: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> numer_pokoju;
		}
	}
	//sprawdzenie czy pokój jest dostêpny w podanym terminie
	while (czy_dostepny_w_przedziale(numer_pokoju, data_od, data_do) == false) {
		usun_linie();
		cout << "Pokój niedostêpny. Podaj inny pokój: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> numer_pokoju;
		//zabezpiecznie by nie wpisaæ nieistniej¹cego pokoju
		while (cin.fail() || znajdz_pokoj(numer_pokoju) == nullptr) {
			usun_linie();
			cout << "Nie ma takiego pokoju: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> numer_pokoju;
		}
	}
	Pokoj* pokoj = znajdz_pokoj(numer_pokoju);

	//pobranie danych goœcia od u¿ytkownika
	cout << "Imiê goœcia: ";
	cin >> imie;
	cout << "Nazwisko goœcia: ";
	cin >> nazwisko;
	cout << "Wiek goœcia: ";
	cin >> wiek;
	while (cin.fail()) {
		usun_linie();
		cout << "Wpisz poprawny wiek: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> wiek;
	}
	while (wiek < 18) {
		for (int i = 0; i < 3; i++) {
			usun_linie();
		}
		cout << "Goœæ musi byæ pe³noletni!" << endl;
		cout << "Imiê goœcia: ";
		cin >> imie;
		cout << "Nazwisko goœcia: ";
		cin >> nazwisko;
		cout << "Wiek goœcia: ";
		cin >> wiek;
		while (cin.fail()) {
			usun_linie();
			cout << "Wpisz poprawny wiek: ";
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> wiek;
		}
	}
	Gosc* gosc = new Gosc(imie, nazwisko, wiek);
	dodaj_goscia(gosc);

	bool potwierdzenie = true;
	int decyzja{};
	cout << endl << "Czy zapisaæ tê rezerwacjê? [1 - tak/2 - nie] ";
	cin >> decyzja;
	cout << endl;
	if (decyzja == 1) {
		potwierdzenie = true;
	}
	else if (decyzja == 2) {
		potwierdzenie = false;
	}
	while (cin.fail() || (decyzja != 1 && decyzja != 2)) {
		cout << "Niepoprawna odpowiedŸ. Wybierz jeszcze raz ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> decyzja;
	}

	if (potwierdzenie == true) {
		//tworzenie i dodanie nowej rezerwacji
		Rezerwacja* rezerwacja = new Rezerwacja(rezerwacje.size() + 1, gosc, pokoj, data_od, data_do);
		rezerwacje.push_back(rezerwacja);
		cout << "Rezerwacja numer " << rezerwacja->get_id() << " zosta³a zapisana" << endl;
	}
	else {
		cout << "Rezerwacja nie zosta³a zapisana" << endl;
		potwierdzenie = true;
	}
}

//funkcja wypisuj¹ca dane rezerwacji o podanym numerze
void Hotel::zobacz_rezerwacje(int numer_rezerwacji) {
	for (auto& rezerwacja : rezerwacje) {
		if (rezerwacja->get_id() == numer_rezerwacji) {
			Gosc* gosc = rezerwacja->get_gosc();
			Pokoj* pokoj = rezerwacja->get_pokoj();
			cout << "Rezerwacja numer " << numer_rezerwacji << ":" << endl;
			cout << "Goœæ: " << gosc->get_imie() << " " << gosc->get_nazwisko() << endl;
			cout << "Numer pokoju: " << pokoj->get_id() << endl;
			cout << "Daty: ";
			pokaz_przedzial(rezerwacja->get_data_poczatek(), rezerwacja->get_data_koniec());
			cout << endl;
			return;
		}
	}
	cout << "Nie znaleziono rezerwacji o numerze " << numer_rezerwacji << "." << endl;
}

//funkcja, która usuwa rezerwacje
void Hotel::anuluj_rezerwacje(int numer_rezerwacji) {
	for (auto i = rezerwacje.begin(); i != rezerwacje.end(); i++) {
		if ((*i)->get_id() == numer_rezerwacji) {
			(*i)->set_id(0);
			cout << "Rezerwacja numer " << numer_rezerwacji << " zostala anulowana." << endl;
			return;
		}
	}
	cout << "Nie znaleziono rezerwacji o numerze " << numer_rezerwacji << "." << endl;
}

//funkcja wypisuj¹ca listê rezerwacji
void Hotel::lista_rezerwacji() {
	int a{};
	if (rezerwacje.begin() == rezerwacje.end()) {
		cout << "Brak rezerwacji." << endl;
		return;
	}
	else {
		for (auto i = rezerwacje.begin(); i != rezerwacje.end(); i++) {
			if ((*i)->get_id() == 0) {
				continue;
			}
			tm data_od = (*i)->get_data_poczatek();
			tm data_do = (*i)->get_data_koniec();
			cout << (*i)->get_id() << ". ";
			pokaz_przedzial(data_od, data_do);
			cout << " goœæ: " << (*i)->get_gosc()->get_imie() << " " << (*i)->get_gosc()->get_nazwisko() << " numer pokoju: " << (*i)->get_pokoj()->get_id() << endl;
			a++;
		}
	}
	if (a == 0) {
		cout << "Brak rezerwacji." << endl;
		return;
	}
}

//funkcja licz¹ca liczbê dni rezerwacji
int Hotel::licz_dni(int numer_rezerwacji) {
	for (const auto& rezerwacja : rezerwacje) {
		if (rezerwacja->get_id() == numer_rezerwacji) {
			int dni{};
			tm data_od = rezerwacja->get_data_poczatek();
			tm data_do = rezerwacja->get_data_koniec();
			int odr = data_od.tm_year;
			int odm = data_od.tm_mon;
			int odd = data_od.tm_mday;
			int dor = data_do.tm_year;
			int dom = data_do.tm_mon;
			int dod = data_do.tm_mday;
			if (odm == dom && odr == dor) {
				dni = dod - odd;
			}
			else if (odr == dor) {
				dni += miesiace(odm, odr) - odd;
				if (odm == 2 && odr % 4 == 0) {
					dni += 1;
				}
				for (int miesiac = odm + 1; miesiac < dom; miesiac++) {
					dni += miesiace(miesiac, odr);
				}
				dni += dod;
			}
			else {
				dni += miesiace(odm, odr) - odd;
				dni += dod;
			}
			return dni;
		}
	}
}

//funkcja sprawdzaj¹ca ile osób jest w pokoju w danej rezerwacji
int Hotel::ilosc_osob(int numer_rezerwacji) {
	for (auto& rezerwacja : rezerwacje) {
		if (rezerwacja->get_id() == numer_rezerwacji) {
			Pokoj* pokoj = rezerwacja->get_pokoj();
			return pokoj->get_typ_pokoju();
		}
	}
}

//funkcja sprawdzaj¹ca czy dany pokój jest dostêpny w podanym dniu
bool Hotel::czy_dostepny(int numer_pokoju, tm data) {
	for (const auto& rezerwacja : rezerwacje) {
		if (rezerwacja->get_pokoj()->get_id() == numer_pokoju) {
			if (rezerwacja->get_id() == 0) {
				continue;
			}
			tm data_od = rezerwacja->get_data_poczatek();
			tm data_do = rezerwacja->get_data_koniec();
			if (data_w_przedziale(data_od, data_do, data) == true) {
				return false;
			}
		}
	}
	return true;
}

//funkcja sprawdzaj¹ca czy dany pokój jest dostêpny w danym przedziale czasowym
bool Hotel::czy_dostepny_w_przedziale(int numer_pokoju, tm data_od, tm data_do) {
	tm sprawdz = data_od;
	if (data_od.tm_mon == data_do.tm_mon) {
		for (int i = data_od.tm_mday; i <= data_do.tm_mday; i++) {
			sprawdz.tm_mday = i;
			if (czy_dostepny(numer_pokoju, sprawdz) == false) {
				return false;
			}
		}
	}
	else if (data_od.tm_mon != data_do.tm_mon) {
		for (int i = data_od.tm_mday; i <= miesiace(data_od.tm_mon, data_od.tm_year); i++) {
			sprawdz.tm_mday = i;
			if (czy_dostepny(numer_pokoju, sprawdz) == false) {
				return false;
			}
		}
		for (int i = 1; i <= sprawdz.tm_mday; i++) {
			sprawdz.tm_mday = i;
			sprawdz.tm_mon = data_do.tm_mon;
			if (czy_dostepny(numer_pokoju, sprawdz) == false) {
				return false;
			}
		}
	}
	return true;
}

//funkcja usuwaj¹ca liniê tekstu w konsoli
void usun_linie() {
	cout << "\x1b[1A"; // Przesuniêcie kursora do góry o 1 liniê
	cout << "\x1b[2K"; // Wyczyszczenie linii
}

//funkcja zwracaj¹ca liczbê dni miesi¹ca danego roku
int miesiace(int miesiac, int rok) {
	switch (miesiac) {
	case 1:  // styczeñ
	case 3:  // marzec
	case 5:  // maj
	case 7:  // lipiec
	case 8:  // sierpieñ
	case 10: // paŸdziernik
	case 12: // grudzieñ
		return 31;
	case 4:  // kwiecieñ
	case 6:  // czerwiec
	case 9:  // wrzesieñ
	case 11: // listopad
		return 30;
	case 2:
		if (rok % 4 == 0) {
			return 29;
		}
		else {
			return 28;
		}
	default:
		return 0;
	}
}

//funkcja wypisuj¹ca datê
void pokaz_date(tm data) {
	cout << data.tm_mday << "." << data.tm_mon << "." << data.tm_year;
}

//funkcja wypisuj¹ca przedzia³ datowy
void pokaz_przedzial(tm data_od, tm data_do) {
	pokaz_date(data_od);
	cout << " - ";
	pokaz_date(data_do);
	cout << endl;
}


//funkcja pobieraj¹ca datê od u¿ytkownika
tm pobierz_date() {
	int rok, miesiac, dzien;
	cout << "Rok: ";
	cin >> rok;
	//zabezpieczenie aby podaæ rok w przedziale 2023-2030
	while (cin.fail() || rok < 2023 || rok > 2030) {
		usun_linie();
		cout << "Wpisz poprawny rok: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> rok;
	}
	cout << "Miesi¹c: ";
	cin >> miesiac;
	//zabezpiecznie by wpisaæ poprawny miesi¹c 
	while (cin.fail() || miesiac > 12 || miesiac < 1) {
		usun_linie();
		cout << "Wpisz poprawny miesi¹c liczb¹: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> miesiac;
	}
	cout << "Dzieñ: ";
	cin >> dzien;
	//zabezpiecznie by wpisaæ poprawny dzieñ
	while (cin.fail() || dzien > miesiace(miesiac, rok) || dzien < 0) {
		usun_linie();
		cout << "Wpisz poprawny dzieñ: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> dzien;
	}

	tm data{};
	data.tm_year = rok;
	data.tm_mon = miesiac;
	data.tm_mday = dzien;

	return data;
}

//funkcja sprawdzaj¹ca czy dana data jest podanym przedziale
bool data_w_przedziale(tm data_od, tm data_do, tm data) {
	if (data.tm_year == data_od.tm_year && data.tm_year == data_do.tm_year &&
		data.tm_mon == data_od.tm_mon && data.tm_mon == data_do.tm_mon &&
		data.tm_mday >= data_od.tm_mday && data.tm_mday <= data_do.tm_mday) {
		return true;
	}
	else if (data.tm_year == data_od.tm_year && data.tm_year == data_do.tm_year &&
		data.tm_mon > data_od.tm_mon && data.tm_mon < data_do.tm_mon) {
		return true;
	}
	else if (data.tm_year == data_od.tm_year && data.tm_year == data_do.tm_year &&
		data.tm_mon == data_od.tm_mon && data.tm_mon < data_do.tm_mon &&
		data.tm_mday >= data_od.tm_mday) {
		return true;
	}
	else if (data.tm_year == data_od.tm_year && data.tm_year == data_do.tm_year &&
		data.tm_mon > data_od.tm_mon && data.tm_mon == data_do.tm_mon &&
		data.tm_mday <= data_do.tm_mday) {
		return true;
	}
	else if (data.tm_year == data_od.tm_year && data.tm_year < data_do.tm_year) {
		if ((data.tm_mon == data_od.tm_mon && data.tm_mday >= data_od.tm_mday) || data.tm_mon > data_od.tm_mday) {
			return true;
		}
	}
	else if (data.tm_year > data_od.tm_year && data.tm_year == data_do.tm_year) {
		if ((data.tm_mon == data_do.tm_mon && data.tm_mday <= data_do.tm_mday) || data.tm_mon < data_do.tm_mday) {
			return true;
		}
	}
	else {
		return false;
	}
}

//funkcja sprawdzaj¹ca czy podany przedzia³ jest w dobrej kolejnoœci
bool kolejnosc_przedzialu(tm data_od, tm data_do) {
	if (data_do.tm_year < data_od.tm_year ||
		(data_do.tm_mon < data_od.tm_mon && data_do.tm_year == data_od.tm_year) ||
		(data_do.tm_mday < data_od.tm_mday && data_do.tm_mon == data_od.tm_mon && data_do.tm_year == data_od.tm_year)) {
		return false;
	}
	else {
		return true;
	}
}

//funkcja sprawdzaj¹ca czy podany przedzia³ jest nie d³u¿szy ni¿ 2 miesi¹ce
bool dlugosc_przedzialu(tm data_od, tm data_do) {
	if ((data_do.tm_year - data_od.tm_year > 1) ||
		(data_do.tm_year == data_od.tm_year && data_do.tm_mon - data_od.tm_mon > 1) ||
		(data_do.tm_year != data_od.tm_year && (data_od.tm_mon != 12 || data_do.tm_mon != 1))) {
		return false;
	}
	else {
		return true;
	}
}