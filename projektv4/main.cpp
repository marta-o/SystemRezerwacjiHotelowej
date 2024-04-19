#include "klasy.h"

int main() {
	//tworzenie hotelu
	Hotel hotel("weekend");

	//tworzenie pokoi
	hotel.dodaj_pokoj(new Pokoj(1, 1));
	hotel.dodaj_pokoj(new Pokoj(2, 1));
	hotel.dodaj_pokoj(new Pokoj(3, 2));
	hotel.dodaj_pokoj(new Pokoj(4, 2));
	hotel.dodaj_pokoj(new Pokoj(5, 3));
	hotel.dodaj_pokoj(new Pokoj(6, 4));

	double cena_za_dobe = 100;

	//ustawienie polskich znaków
	setlocale(LC_ALL, "Polish");

	//logo
	string logo = R"(
 _    _   ____   _______  ______  _            _           _  ______   ______   _   _   ______   _     _   _ __ _ 
| |  | |/  __  \|__   __||  ____|| |           \ \        / /|  ____| |  ____| | | / / |  ____| |\ \  | | |  __\ \
| |__| || |  | |   | |   | |____ | |            \ \  /\  / / | |____  | |____  | |/ /  | |____  | \ \ | | | |  | |
|  __  || |  | |   | |   |  ____|| |             \ \/  \/ /  |  ____| |  ____| |   \   |  ____| | |\ \| | | |  | |
| |  | || |__| |   | |   | |____ | |____          \ \/\/ /   | |____  | |____  | |\ \  | |____  | | \ \ | | |__| |
|_|  |_| \____/    |_|   |______||______|          \/  \/    |______| |______| |_| \_\ |______| |_|  \_\| |____/_/
                                                             
)";

	cout << logo;
	cout << endl << "Wciœnij dowolny klawisz by kontynuowaæ...";

	//czekanie na klawisz
	_getch();

	bool kontynuacja = true;

	//wybieranie opcji z menu
	while (kontynuacja) {
		//czyszczenie ekranu
		system("cls");

		int x;
		x = menu();

		int numer{};
		tm data1{}, data2{};
		double kwota{};

		bool potwierdzenie = true;
		int odp{};

		switch (x) {
		case 1:
			system("cls");
			cout << "DODAWANIE REZERWACJI" << endl << endl;
			hotel.dodaj_rezerwacje();
			break;
		case 2:
			system("cls");
			cout << "SZUKANIE REZERWACJI" << endl << endl;
			cout << "Podaj numer rezerwacji: ";
			cin >> numer;
			while (cin.fail()) {
				usun_linie();
				cout << "Niepoprawna odpowiedŸ. Podaj poprawny numer rezerwacji: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> numer;
			}
			hotel.zobacz_rezerwacje(numer);
			break;
		case 3:
			system("cls");
			cout << "ANULOWANIE REZERWACJI" << endl << endl;
			cout << "Podaj numer rezerwacji: ";
			cin >> numer;
			while (cin.fail()) {
				usun_linie();
				cout << "Niepoprawna odpowiedŸ. Podaj numer rezerwacji: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> numer;
			}
			cout << endl << "Czy anulowaæ rezerwacjê numer " << numer << "? [1 - tak / 2 - nie] ";
			cin >> odp;
			cout << endl;
			if (odp == 1) {
				potwierdzenie = true;
			}
			else if (odp == 2) {
				potwierdzenie = false;
			}
			while (cin.fail() || (odp != 1 && odp != 2)) {
				cout << "Niepoprawna odpowiedŸ. Wybierz jeszcze raz ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> odp;
			}

			if (potwierdzenie == true) {
				hotel.anuluj_rezerwacje(numer);
			}
			else {
				cout << "Rezerwacja nie zosta³a anulowana." << endl;
			}

			break;
		case 4:
			system("cls");
			cout << "INFORMACJE O POKOJU" << endl << endl;
			cout << "Podaj numer pokoju: ";
			cin >> numer;
			while (cin.fail()) {
				usun_linie();
				cout << "Niepoprawna odpowiedŸ. Podaj poprawny numer pokoju: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> numer;
			}
			hotel.informacje_o_pokoju(hotel.znajdz_pokoj(numer));
			break;
		case 5:
			system("cls");
			cout << "LISTA POKOI" << endl << endl;
			hotel.lista_pokoi();
			break;
		case 6:
			system("cls");
			cout << "LISTA GOŒCI" << endl << endl;
			hotel.lista_gosci();
			break;
		case 7:
			system("cls");
			cout << "LISTA REZERWACJI" << endl << endl;
			hotel.lista_rezerwacji();
			break;
		case 8:
			system("cls");
			cout << "CA£KOWITA KWOTA ZA REZERWACJÊ" << endl << endl;
			cout << "Podaj numer rezerwacji: ";
			cin >> numer;
			while (cin.fail()) {
				usun_linie();
				cout << "Niepoprawna odpowiedŸ. Podaj poprawny numer rezerwacji:  ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> numer;
			}
			if (hotel.znajdz_rezerwacje(numer) == nullptr) {
				cout << "Nie ma takiej rezerwacji" << endl;
				break;
			}
			kwota = (double)hotel.licz_dni(numer) * cena_za_dobe * (double)hotel.ilosc_osob(numer);
			if (kwota == 0) {
				kwota = 50 * (double)hotel.ilosc_osob(numer);
			}
			cout << "Kwota ca³kowita za rezerwacjê numer " << numer << ": " << kwota << " z³" << endl;
			break;
		case 9:
			system("cls");
			cout << "SPRAWDZANIE CZY DANY POKÓJ JEST DOSTÊPNY W DANYM TERMINIE" << endl << endl;
			cout << "Podaj numer pokoju: ";
			cin >> numer;
			while (cin.fail() || hotel.znajdz_pokoj(numer) == nullptr) {
				usun_linie();
				cout << "Nie ma takiego pokoju. Podaj jeszcze raz numer pokoju: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> numer;
			}
			cout << "Podaj datê pocz¹tkow¹: " << endl;
			data1 = pobierz_date();
			cout << "Podaj datê koñcow¹: " << endl;
			data2 = pobierz_date();
			while (kolejnosc_przedzialu(data1, data2) == false || dlugosc_przedzialu(data1, data2) == false) {
				for (int i = 0; i < 8; i++) {
					usun_linie();
				}
				cout << "Nie mo¿na sprawdziæ takiego terminu." << endl;
				cout << "Data przyjazdu:" << endl;
				data1 = pobierz_date();
				cout << "Data wyjazdu: " << endl;
				data2 = pobierz_date();
			}

			if (hotel.czy_dostepny_w_przedziale(numer, data1, data2) == true) {
				cout << endl << "Pokój dostêpny w terminie ";
				pokaz_przedzial(data1, data2);
				cout << endl;
			}
			else {
				cout << endl << "Pokój niedostêpny w terminie ";
				pokaz_przedzial(data1, data2);
				cout << endl;
			}
			break;
		case 10:
			system("cls");
			cout << "LISTA DOSTÊPNYCH POKOI" << endl << endl;
			cout << "Podaj datê pocz¹tkow¹: " << endl;
			data1 = pobierz_date();
			cout << "Podaj datê koñcow¹: " << endl;
			data2 = pobierz_date();
			while (kolejnosc_przedzialu(data1, data2) == false || dlugosc_przedzialu(data1, data2) == false) {
				for (int i = 0; i < 8; i++) {
					usun_linie();
				}
				cout << "Nie mo¿na sprawdziæ takiego terminu." << endl;
				cout << "Data przyjazdu:" << endl;
				data1 = pobierz_date();
				cout << "Data wyjazdu: " << endl;
				data2 = pobierz_date();
			}
			for (int i = 1; i <= hotel.pokoje.size(); i++) {
				if (hotel.czy_dostepny_w_przedziale(i, data1, data2) == true) {
					Pokoj* pokoj = hotel.znajdz_pokoj(i);
					hotel.informacje_o_pokoju(pokoj);
					numer++;
				}
			}
			if (numer == 0) {
				cout << endl << "Brak dostêpnych pokoi." << endl;
			}
			break;
		case 11:
			system("cls");
			cout << "LISTA ZAREZERWOWANYCH POKOI" << endl << endl;
			cout << "Podaj datê pocz¹tkow¹: " << endl;
			data1 = pobierz_date();
			cout << "Podaj datê koñcow¹: " << endl;
			data2 = pobierz_date();
			while (kolejnosc_przedzialu(data1, data2) == false || dlugosc_przedzialu(data1, data2) == false) {
				for (int i = 0; i < 8; i++) {
					usun_linie();
				}
				cout << "Nie mo¿na sprawdziæ takiego terminu." << endl;
				cout << "Data przyjazdu:" << endl;
				data1 = pobierz_date();
				cout << "Data wyjazdu: " << endl;
				data2 = pobierz_date();
			}
			for (int i = 1; i <= hotel.pokoje.size(); i++) {
				if (hotel.czy_dostepny_w_przedziale(i, data1, data2) == false) {
					Pokoj* pokoj = hotel.znajdz_pokoj(i);
					hotel.informacje_o_pokoju(pokoj);
					numer++;
				}
			}
			if (numer == 0) {
				cout << endl << "Wszystkie pokoje s¹ wolne." << endl;
			}
			break;
		case 12:
			system("cls");
			cout << "KONIEC. DO WIDZENIA" << endl << endl;
			return 0;

		default:
			cout << "Nie ma takiej opcji w menu!" << endl;
			break;
		}

		//pytanie u¿ytkownika czy chce kontynuowaæ
		int decyzja{};
		cout << endl << "Czy chcesz kontynuowaæ? [1 - tak/2 - nie] ";
		cin >> decyzja;
		if (decyzja == 1) {
			kontynuacja = true;
		}
		else if (decyzja == 2) {
			kontynuacja = false;
		}
		while (cin.fail() || (decyzja != 1 && decyzja != 2)) {
			cout << "Niepoprawna odpowiedŸ. Wybierz jeszcze raz ";
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> decyzja;
		}
	}

	system("cls");
	cout << "KONIEC. DO WIDZENIA" << endl;
	return 0;
}