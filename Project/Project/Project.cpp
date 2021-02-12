/*Aplicatie pentru gestiunea unui atelier de reparatii produse electrocasnice pentru care se inregistreaza aparatele electrocasnice primite,
care au asociate liste cu interventii si costurile acestora. Aplicatia permite adaugarea unui obiect electrocasnic in atelier si
stabilirea listei de interventii, determinarea costului reparatiei pentru un obiect cat si pentru toate obiectele din atelier, stergerea
aparatelor, cat si alte functionalitati.*/

#include <iostream>
#include <string>
#include <list>

using namespace std;

class DataSosireAparat {
public:
	int zi, luna, an;
	friend istream& operator >> (istream& is, DataSosireAparat& d)
	{
		cout << "Dati anul sosirii aparatului: "; is >> d.an;
		cout << "Dati luna (1-12) sosirii aparatului: "; is >> d.luna;
		cout << "Dati ziua (1-31) sosirii aparatului: "; is >> d.zi;
		return is;
	}
	friend ostream& operator << (ostream& os, const DataSosireAparat& d)
	{
		os << "Anul sosirii: " << d.an << endl;
		os << "Luna sosirii: " << d.luna << endl;
		os << "Ziua sosirii: " << d.zi << endl;
		return os;
	}

	friend bool operator > (const DataSosireAparat& d1, const DataSosireAparat& d2) {
		if (d1.an > d2.an)
			return true;
		if (d1.an == d2.an)
			if (d1.luna > d2.luna)
				return true;
		if (d1.an == d2.an)
			if (d1.luna == d2.luna)
				if (d1.zi >= d2.zi)
					return true;
		return false;
	}

	friend bool operator < (const DataSosireAparat& d1, const DataSosireAparat& d2) {
		if (d1.an < d2.an)
			return true;
		if (d1.an == d2.an)
			if (d1.luna < d2.luna)
				return true;
		if (d1.an == d2.an)
			if (d1.luna == d2.luna)
				if (d1.zi <= d2.zi)
					return true;
		return false;
	}
};

int v[10000] = { 0 };

class Client {
	int id;
	string nume;
	string prenume;
	string email;
	long int NumarTelefon;
	long long int CNP;
	bool dejainmemorie = false;
public:
	Client() {
		this->id = -1;
		this->nume = "Necunoscut";
		this->prenume = "Necunoscut";
		this->email = "Necunoscut";
		this->NumarTelefon = 0;
		this->CNP = 0;
	}
	Client(int id, string nume, string prenume, string email, long int nrtel, long long int cnp) {
		this->id = id;
		this->nume = nume;
		this->prenume = prenume;
		this->email = email;
		this->NumarTelefon = nrtel;
		this->CNP = cnp;
	}
	void setId(int id) {
		this->id = id;
	}
	void setNume(string nume) {
		this->nume = nume;
	}
	void setPrenume(string prenume) {
		this->prenume = prenume;
	}
	void setEmail(string email) {
		this->email = email;
	}
	void setTelefon(long int numar) {
		this->NumarTelefon = numar;
	}
	void setCNP(long long int cnp) {
		this->CNP = cnp;
	}
	int getId() {
		return id;
	}
	string getNume() {
		return nume;
	}
	string getPrenume() {
		return prenume;
	}
	string getEmail() {
		return email;
	}
	long int getTelefon() {
		return NumarTelefon;
	}
	long long int getCNP() {
		return CNP;
	}
	bool getMemorie() {
		return dejainmemorie;
	}
	friend istream& operator >> (istream& is, Client &c) {
		cout << "Introduceti id-ul clientului: ";
		is >> c.id;
		is.ignore();
		if (v[c.id] == 0) {
			cout << "Introduceti numele clientului: ";
			getline(is, c.nume);
			cout << "Introduceti prenumele clientului: ";
			getline(is, c.prenume);
			cout << "Introduceti CNP-ul clientului: ";
			is >> c.CNP;
			cout << "Introduceti numarul de telefon al clientului: ";
			is >> c.NumarTelefon;
			cout << "Introduceti adresa de email a clientului: ";
			is >> c.email;
		}
		else
		{
			c.dejainmemorie = true;
			cout << "Datele clientului deja introdus vor fi copiate. ";
		}
		v[c.id]++;
		return is;
	}
	friend ostream& operator <<(ostream& os, const Client& c) {
		os << "Id-ul clientului: " << c.id << endl;
		os << "Numele clientului: " << c.nume << endl;
		os << "Prenumele clientului: " << c.prenume << endl;
		os << "CNP-ul clientului: " << c.CNP << endl;
		os << "Numarul de telefon al clientului: " << c.NumarTelefon << endl;
		os << "Email-ul clientului: " << c.email << endl;
		return os;
	}
};

class Interventie {
	string nume;
	float pret;
public:
	string getNume() {
		return nume;
	}
	float getPret() {
		return pret;
	}
	Interventie() {
	}
	friend istream& operator >> (istream& is, Interventie& interventie)
	{
		cout << "Dati numele reparatiei: ";
		is.ignore();
		getline(is, interventie.nume);
		cout << "Dati pretul reparatiei: "; is >> interventie.pret;
		return is;
	}
	friend ostream& operator << (ostream& os, const Interventie& interventie)
	{
		os << "Numele interventiei: " << interventie.nume << endl;
		os << "   Pretul interventiei: " << interventie.pret << endl;
		return os;
	}
};

class Aparat {
	string nume;
	bool statusReparat = false;
	bool statusRidicat = false;
public:
	Client c;
	DataSosireAparat d;
	list <Interventie> interventii;
	bool getstatusReparat() {
		return statusReparat;
	}
	bool getstatusRidicat() {
		return statusRidicat;
	}
	void setstatusReparat(bool status) {
		statusReparat = status;
	}
	void setstatusRidicat(bool status) {
		statusRidicat = status;
	}
	bool operator < (const Aparat& a) {
		if (d < a.d) {
			return true;
		}
		return false;
	}
	void adaugaInterventie(Interventie& i)
	{
		interventii.push_back(i);
	}
	void stergeInterventie(int pozitie) {
		list <Interventie>::iterator i = interventii.begin();
		advance(i, pozitie);
		interventii.erase(i);
	}
	friend istream& operator >> (istream& is, Aparat& aparat)
	{
		cout << "Dati numele aparatului: ";
		is.ignore();
		getline(is, aparat.nume);
		cout << "Introduceti datele clientului: " << endl;
		is >> aparat.c;
		cout << "Introduceti data sosirii aparatului: " << endl;
		is >> aparat.d;
		return is;
	}
	friend ostream& operator << (ostream& os, Aparat a)
	{
		int counter = 0;
		os << a.nume;
		os << ". Aparatul " << a.nume << " contine " << a.interventii.size() << " interventii:" << endl;
		for (list <Interventie>::iterator i = a.interventii.begin(); i != a.interventii.end(); i++)
		{
			os << counter << ": " << *i;
			counter++;
		}
		os << a.c;
		os << a.d;
		os << "Statusul reparatiei: ";
		if (a.statusReparat) {
			os << "Reparat." << endl;
		}
		else
		{
			os << "Nereparat." << endl;
		}
		os << "Status ridicare client: ";
		if (a.statusRidicat) {
			os << "Ridicat." << endl;
		}
		else
		{
			os << "Neridicat." << endl;
		}
		os << endl;
		return os;
	}
	float calculeazaCost()
	{
		float costReparatie = 0;
		for (list <Interventie>::iterator i = interventii.begin(); i != interventii.end(); i++)
		{
			costReparatie = costReparatie + (*i).getPret();
		}
		return costReparatie;
	}
};

class Atelier {
public:
	list <Aparat> aparate;
	void AdaugaAparat(const Aparat& a) {
		aparate.push_back(a);
	}
	void StergeAparat(int pozitie) {
		list <Aparat>::iterator i = aparate.begin();
		advance(i, pozitie);
		v[(*i).c.getId()] = 0;
		aparate.erase(i);
	}
	float CalculeazaCostTotal() {
		float costTotal = 0;
		for (list <Aparat>::iterator i = aparate.begin(); i != aparate.end(); i++) {
			costTotal += (*i).calculeazaCost();
		}
		return costTotal;
	}
	void CalculeazaCostClient() {
		int id;
		cout << "Introduceti id-ul clientului pentru care vrei sa calculati costurile: "; cin >> id;
		while (v[id] == 0) {
			cout << "Clientul cu id-ul " << id << " nu exista. Va rugam introduceti un id valid!" << endl;
			cin >> id;
		}
		float costClient = 0;
		for (list <Aparat>::iterator i = aparate.begin(); i != aparate.end(); i++) {
			if ((*i).c.getId() == id) {
				costClient += (*i).calculeazaCost();
			}
		}
		cout << "Costul pe care clientul cu id-ul " << id << " trebuie sa-l plateasca este in valoare de: " << costClient << " lei" << endl;
	}
	friend ostream& operator << (ostream& os, Atelier a) {
		if (a.aparate.empty()) {
			cout << "Atelierul este gol.";
		}
		else {
			int counter = 0;
			os << "Atelierul contine:" << endl;
			for (list <Aparat>::iterator i = a.aparate.begin(); i != a.aparate.end(); i++) {
				os << counter << ": " << *i;
				counter++;
			}
		}
		return os;
	}
	void IndiceAparatValid(unsigned int &numar) {
		cin >> numar;
		while (numar >= aparate.size())
		{
			cout << "Introdu un indice valid!" << endl;
			cin >> numar;
		}
	}
	void IndiceAparatValidPentruStergere(unsigned int &pozitieAp) {
		cin >> pozitieAp;
		list <Aparat>::iterator i = aparate.begin();
		advance(i, pozitieAp);
		while (pozitieAp >= aparate.size() || (*i).interventii.empty()) {
			cout << "Introdu un indice valid, care contine interventii!" << endl;
			cin >> pozitieAp;
		}
	}
	void IndiceInterventieValid(unsigned int &pozitieAp, unsigned int &pozitieInt) {
		cin >> pozitieInt;
		list <Aparat>::iterator i = aparate.begin();
		advance(i, pozitieAp);
		while (pozitieInt >= (*i).interventii.size())
		{
			cout << "Introdu un indice valid!" << endl;
			cin >> pozitieInt;
		}
	}
	void AdaugaDatePentruClientiDejaExistenti(Aparat& a) {
		if (a.c.getMemorie()) {
			for (list <Aparat>::iterator i = aparate.begin(); i != aparate.end(); i++) {
				if ((*i).c.getId() == a.c.getId()) {
					a.c.setNume((*i).c.getNume());
					a.c.setPrenume((*i).c.getPrenume());
					a.c.setEmail((*i).c.getEmail());
					a.c.setTelefon((*i).c.getTelefon());
					a.c.setCNP((*i).c.getCNP());
				}
			}
		}
	}
	void OrdineReparatiiAparate() {
		aparate.sort();
		cout << "Ordinea in care trebuie reparate aparatele este: " << endl;
		for (list <Aparat>::iterator i = aparate.begin(); i != aparate.end(); i++) {
			if ((*i).getstatusReparat() == false) {
				cout << *i << " " << endl;
			}
		}
	}
	void AfiseazaAparateNeridicate() {
		for (list <Aparat>::iterator i = aparate.begin(); i != aparate.end(); i++) {
			if ((*i).getstatusReparat() == true) {
				cout << *i << " " << endl;
			}
		}
	}
	void schimbastatusReparat() {
		if (aparate.empty()) {
			cout << "Nu exista aparate in atelier!" << endl;
		}
		else {
			unsigned int id;
			cout << "Introdu id-ul aparatului care a fost reparat: "; cin >> id;
			while (id >= aparate.size()) {
				cout << "Introdu un id valid!" << endl;
				cin >> id;
			}
			list <Aparat>::iterator i = aparate.begin();
			advance(i, id);
			(*i).setstatusReparat(true);
			cout << "Statusul a fost schimbat cu succes!" << endl;
		}
	}
	void schimbastatusRidicat() {
		if (aparate.empty()) {
			cout << "Nu exista aparate in atelier!" << endl;
		}
		else {
			unsigned int id;
			cout << "Introdu id-ul aparatului care a fost ridicat de catre client: "; cin >> id;
			while (id >= aparate.size()) {
				cout << "Introdu un id valid!" << endl;
				cin >> id;
			}
			list <Aparat>::iterator i = aparate.begin();
			advance(i, id);
			(*i).setstatusRidicat(true);
			StergeAparat(id);
			cout << "Statusul aparatului a fost schimbat cu succes, iar acesta a fost sters din baza de date a atelierului." << endl;
		}
	}
};

void Introducere() {
	cout << "Bun venit! Va aflati in aplicatia pentru gestiunea unui atelier de reparatii produse electrocasnice.";
	cout << endl;
	cout << "Pentru a vizualiza meniul, va rugam introduceti o tasta de la 1 la 9" << endl;
	int continuare;
	cin >> continuare;
	while (!(continuare >= 1 && continuare <= 9)) {
		cout << "Introdu te rog o cifra de la 1 la 9!" << endl;
		cin >> continuare;
	}
}

void AfiseazaMeniu() {
	cout << "1: Adauga un aparat electrocasnic;" << endl;
	cout << "2: Adauga o reparatie pentru un anumit aparat;" << endl;
	cout << "3: Calculeaza costul reparatiilor pentru un anumit aparat;" << endl;
	cout << "4: Calculeaza costul reparatiilor pentru toate aparatele;" << endl;
	cout << "5: Calculeaza costul reparatiilor pentru un anumit client;" << endl;
	cout << "6: Vizualizare atelier;" << endl;
	cout << "7: Sterge interventie pentru un anumit aparat;" << endl;
	cout << "8: Sterge aparat;" << endl;
	cout << "9: Vizualizeaza ordinea in care trebuie reparate aparatele;" << endl;
	cout << "10: Afiseaza aparatele neridicate;" << endl;
	cout << "11: Schimba statusul unui aparat in reparat;" << endl;
	cout << "12: Schimba statusul unui aparat in ridicat;" << endl;
	cout << "0: Iesire;" << endl;
	cout << "Introduceti un numar corespondent optiunii dorite!" << endl;
}

int main() {
	int optiune;
	Introducere();
	Atelier a;
	do {
		Aparat ap;
		Interventie i;
		AfiseazaMeniu();
		cin >> optiune;
		Atelier b = a;
		switch (optiune) {
		case 1:
			cin >> ap;
			a.AdaugaDatePentruClientiDejaExistenti(ap);
			a.AdaugaAparat(ap);
			cout << "Aparatul a fost adaugat cu succes!" << endl;
			break;
		case 2:
			unsigned int numar;
			if (a.aparate.empty()) {
				cout << a;
				break;
			}
			else {
				cout << a;
				cout << "Introdu indicele aparatului pentru care vrei sa adaugi interventia." << endl;
				a.IndiceAparatValid(numar);
				cin >> i;
				list <Aparat>::iterator it = a.aparate.begin();
				advance(it, numar);
				(*it).adaugaInterventie(i);
				cout << "Interventia a fost adaugata cu succes!" << endl;
				break;
			}
		case 3:
			if (a.aparate.empty()) {
				cout << a;
				break;
			}
			else {
				cout << a;
				cout << "Introdu indicele aparatului pentru care vrei sa calculezi costul reparatiilor." << endl;
				a.IndiceAparatValid(numar);
				cout << "Costul pentru reparatiile aparatului " << numar << " este: ";
				list <Aparat>::iterator it = a.aparate.begin();
				advance(it, numar);
				cout << (*it).calculeazaCost() << endl;
				break;
			}
		case 4:
			cout << "Costul reparatiilor tuturor aparatelor din atelier este: ";
			cout << a.CalculeazaCostTotal() << endl;
			break;
		case 5:
			if (a.aparate.empty()) {
				cout << a;
				break;
			}
			else
			{
				cout << a;
				a.CalculeazaCostClient();
				break;
			}
		case 6:
			cout << a;
			break;
		case 7:
			unsigned int pozitieAp, pozitieInt;
			if (a.aparate.empty()) {
				cout << a;
				break;
			}
			else {
				cout << a;
				cout << "Introdu indicele aparatului pentru care vrei sa stergi interventia:" << endl;
				a.IndiceAparatValidPentruStergere(pozitieAp);
				cout << "Introdu indicele interventiei pe care doresti sa o stergi:" << endl;
				a.IndiceInterventieValid(pozitieAp, pozitieInt);
				list <Aparat>::iterator it = a.aparate.begin();
				advance(it, pozitieAp);
				(*it).stergeInterventie(pozitieInt);
				cout << "Inregistrarea a fost stearsa cu succes!" << endl;
				break;
			}
		case 8:
			if (a.aparate.empty()) {
				cout << a;
				break;
			}
			else {
				cout << a;
				cout << "Introdu indicele aparatului pe care vrei sa-l stergi:" << endl;
				a.IndiceAparatValid(pozitieAp);
				a.StergeAparat(pozitieAp);
				cout << "Aparatul a fost eliminat cu succes!" << endl;
				break;
			}
		case 9:
			b.OrdineReparatiiAparate();
			break;
		case 10:
			a.AfiseazaAparateNeridicate();
			break;
		case 11:
			a.schimbastatusReparat();
			break;
		case 12:
			a.schimbastatusRidicat();
			break;
		case 0:
			cout << "La revedere!";
			break;
		default:
			cout << "Nu ati ales un numar din meniu." << endl;
		}
		cout << endl << "===========================================" << endl;
	} while (optiune);
	return 0;
}
