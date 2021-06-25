#include "konzola.hpp"
void Konzola::login() {
	std::string korIme;
	std::cout << "Unesite korisnicko ime (-1 da bi se registrovali, 0 da bi izasli): ";
	std::cin >> korIme;
	if (korIme == "-1") {
		stanje = Stanje::REGISTRACIJA;
		return;
	}
	if (korIme == "0") {
		stanje = Stanje::IZLAZ;
		return;
	}
	std::cout << "Unesite sifru: ";
	std::string sifra;
	std::cin >> sifra;
	std::pair<std::string, std::string> konf;
	konf.first = korIme;
	konf.second = sifra;
	std::pair<int, std::string> odg = SQL::loginPass(konf);
	if (odg.first == -1) {
		std::cout << odg.second << std::endl;
	}
	else {
		std::cout << std::endl << "ULOGOVAN" << std::endl << std::endl;
		this->id = odg.first;
		this->username = odg.second;
		this->novac = std::to_string(SQL::novac(this->id));
		stanje = Stanje::GLAVNI;
	}
}
void Konzola::registracija() {
	std::string korIme,sifra,ponSifra;
	int novac;
	std::cout << "Unesite korisnicko ime (-1 da se vratite na login): "; std::cin >> korIme;
	if (korIme == "-1") {
		stanje = Stanje::LOGIN;
		return;
	}
	std::cout << "Unesite sifru: "; std::cin >> sifra;
	std::cout << "Ponovo unesite sifru: "; std::cin >> ponSifra;
	if (sifra != ponSifra) {
		std::cout << std::endl << "SIFRE SE NE POKLAPAJU!" << std::endl << std::endl;
		return;
	}
	std::cout << "Unesite sumu novca: "; std::cin >> novac;
	std::string odg = SQL::registracija(korIme, sifra, novac);
	if (odg != "") {
		std::cout << std::endl << odg << std::endl << std::endl;
		return;
	}
	std::cout << std::endl << "Uspesno registrovan, mozete se ulogovati" << std::endl << std::endl;
	stanje = Stanje::LOGIN;
}
void Konzola::glavni_prozor() {
	this->novac = std::to_string(SQL::novac(this->id));
	std::string upit;
	std::cout << "############################################" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Korisnik : " << this->username << "    Novac : " << this->novac << std::endl;
	std::cout << "##############################################" << std::endl;
	std::cout << "# Izaberi opciju                             #" << std::endl;
	std::cout << "# (1) Prikazi akcije neke firme              #" << std::endl;
	std::cout << "# (2) Prikazi moje akcije                    #" << std::endl;
	std::cout << "# (3) Prikazi moje transakcije               #" << std::endl;
	std::cout << "# (4) Izloguj se                             #" << std::endl;
	std::cout << "# (0) Izlaz                                  #" << std::endl << std::endl;
	std::cout << "##############################################" << std::endl;
	std::cin >> upit;
	if (upit.length() != 1) return;
	switch (upit[0]) {
		case '1':
			prikaziAkcije();
			break;
		case '2':
			stanje = Stanje::AKCIJE;
			break;
		case '3':
			stanje = Stanje::TRANSAKCIJE;
			break;
		case '4':
			stanje = Stanje::LOGIN;
			break;
		case '0':
			stanje = Stanje::IZLAZ;
			break;
	}
	
}
void Konzola::transakcije() {
	Transakcije t = SQL::transakcije(id);
	for (auto x : t) {
		std::cout << x << std::endl;
	}
	stanje = Stanje::GLAVNI;
}
void Konzola::akcije() {
	Akcija a = SQL::akcije(id);
	MapaAkcija mapa = azurirajMapu(a);
	for (auto x : a) {
		std::string boja = "\033[0;32m";
		if (stod(x.cena) > mapa[x.simbol]) boja = "\033[0;31m";
		std::cout << boja;
		std::cout << x << " " << mapa[x.simbol] << " ";
		std::cout << razlika(stod(x.cena),mapa[x.simbol]) << " " << procRazlika(stod(x.cena), mapa[x.simbol]) << "%";
		std::cout << "\033[0;37m" << std::endl;
	}
	std::cout << std::endl << "Da li zelite da kupite ili prodate akcije? (Izlaz po defaultu, k, p): ";
	std::string unos;
	std::cin >> unos;
	if (unos == "k") {
		std::string simbol, kolicina, cena;
		std::cout << "Unesi simbol: "; std::cin >> simbol;
		std::cout << "Unesi kolicinu: "; std::cin >> kolicina;
		Parser parser;
		Podaci trenpod;
		std::time_t tsad = std::time(0);
		long tpre = tsad - 345600;
		std::transform(simbol.begin(), simbol.end(), simbol.begin(), [](unsigned char c) { return std::tolower(c); });
		trenpod = parser(simbol, std::to_string(tsad), std::to_string(tpre));
		if (trenpod.vrati_velicinu() < 1) {
			std::cout << "GRESKA NEPOSTOJECI SIMBOL" << std::endl;
			stanje = Stanje::GLAVNI;
			return;
		}
		double trenAkc = trenpod.vrati_svece()[trenpod.vrati_velicinu() - 1].close;
		int sqlp = SQL::kupi(this->id, simbol, stod(kolicina), trenAkc);
		if (sqlp != 0) {
			std::cout << "NEUSPESNA KUPOVINA!!!" << std::endl;
		}
		else {
			std::cout << "######    KUPLJENO ZA " << trenAkc * std::stoi(kolicina) << "    ######" << std::endl;
		}
	}
	else if (unos == "p") {
		std::string idAkc, kol;
		std::cout << "Unesi id akcije koju zelis prodati: "; std::cin >> idAkc;
		std::cout << "Unesi kolicinu: "; std::cin >> kol;
		std::string simbol = SQL::simbol(std::stoi(idAkc));
		Parser parser;
		Podaci trenpod;
		std::time_t tsad = std::time(0);
		long tpre = tsad - 345600;
		std::transform(simbol.begin(), simbol.end(), simbol.begin(), [](unsigned char c) { return std::tolower(c); });
		trenpod = parser(simbol, std::to_string(tsad), std::to_string(tpre));
		if (trenpod.vrati_velicinu() < 1) {
			std::cout << "GRESKA NEPOSTOJECI SIMBOL" << std::endl;
			stanje = Stanje::GLAVNI;
			return;
		}
		double trenAkc = trenpod.vrati_svece()[trenpod.vrati_velicinu() - 1].close;
		int sqlp = SQL::prodaj(this->id, std::stoi(idAkc),trenAkc ,std::stoi(kol));
		if (sqlp != 0) {
			std::cout << "Neuspesna prodaja akcije" << std::endl;

		}
		else {
			std::cout << "######    PRODATO ZA " << trenAkc * std::stoi(kol) << "    ######" << std::endl;
		}
	}
	stanje = Stanje::GLAVNI;
}
void Konzola::prikaziAkcije() {
	std::string oznaka;
	std::cout << "Unesi oznaku:"; 
	std::cin >> oznaka;
	std::string spc;
	std::cout << "Unesite specificno vreme? (d,N):";
	std::cin >> spc;
	if (spc == "d") {
		std::string tm1;
		std::string tm2;
		std::cout << "Unesite prvi datum : "; std::cin >> tm1;
		std::cout << "Unesite drugi datum : "; std::cin >> tm2;
		podaci = parser(oznaka, tm2, tm1);
	}
	else {
		long tren = Datum::vrati_trenutno();
		podaci = parser(oznaka, std::to_string(tren), std::to_string(tren - 345600));
	}
	std::cout << podaci << std::endl;
	std::cout << std::endl << "Prikazati EMA? (d,N)";
	std::string emaMa; std::cin >> emaMa;
	if (emaMa == "d") {
		int n;
		std::cout << "Unesite n:";
		std::cin >> n;
		std::vector<double> ema = podaci.vrati_Ema(n);
		for (auto x : ema) {
			std::cout << x << std::endl;
		}
	}
	std::cout << std::endl << "Prikazati MA? (d,N)";
	std::cin >> emaMa;
	if (emaMa == "d") {
		int n;
		std::cout << "Unesite n:";
		std::cin >> n;
		std::vector<double> ma = podaci.vrati_Ma(n);
		for (auto x : ma) {
			std::cout << x << std::endl;
		}
	}
}
