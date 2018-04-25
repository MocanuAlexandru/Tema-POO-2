#pragma once
#ifndef __ARBORE_BINAR_CAUTARE_HEADER_
#define __ARBORE_BINAR_CAUTARE_HEADER_
#include "Arbore.h"
using namespace std;
template<class T>
class ArboreBinarCautare : public Arbore {
	//Date membre
protected:
	Nod<T> * rad;
	///Constructori
public:
	ArboreBinarCautare() : Arbore() { rad = nullptr; }
	ArboreBinarCautare(const ArboreBinarCautare& other) {
		rad = CopiazaArbore(other.rad);
		nr_noduri = other.nr_noduri;
	}
	ArboreBinarCautare& operator=(const ArboreBinarCautare& other) {
		StergeArbore(rad);
		rad = CopiazaArbore(other.rad);
		nr_noduri = other.nr_noduri;
		return *this;
	};
	///Destructor
	~ArboreBinarCautare() {
		StergeArbore(rad);
	}
	///operatori de comparare
	bool operator==(const ArboreBinarCautare& other) const {
		if (rad == nullptr && other.rad == nullptr) return true;
		if (rad == nullptr || other.rad == nullptr) return false;
		if (rad->st && rad->dr && other.rad->st && other.rad->dr) return (rad->info == other.rad->info && *rad->st == *other.rad->st && *rad->dr == *other.rad->dr);
		if (rad->st && other.rad->st && rad->dr) return 0;
		if (rad->st && other.rad->st && other.rad->dr) return 0;
		if (rad->st && other.rad->st) return (rad->info == other.rad->info && *rad->st == *other.rad->st);
		if (rad->dr && other.rad->dr && rad->st) return 0;
		if (rad->dr && other.rad->dr && other.rad->st) return 0;
		if (rad->dr && other.rad->dr) return (rad->info == other.rad->info && *rad->dr == *other.rad->dr);
		if (rad->st) return 0;
		if (rad->dr) return 0;
		if (other.rad->st) return 0;
		if (other.rad->dr) return 0;
		return rad->info == other.rad->info;
	}
	bool operator!=(const ArboreBinarCautare& other) const {
		return !(*this == other);
	}
	bool operator<(const ArboreBinarCautare& other) const {
		if (*rad < *other.rad) return true;
		if (*other.rad < *rad) return false;
		if (rad->st) {
			if (other.rad->st) return *rad->st < *other.rad->st;
			return false;
		}
		if (rad->dr) {
			if (other.rad->st) return true;
			if (other.rad->dr) return *rad->dr < *other.rad->dr;
			return false;
		}
		if (other.rad->st) return true;
		if (other.rad->dr) return true;
		return false;
	}
	///operatori matematici
	ArboreBinarCautare operator+(const ArboreBinarCautare& other) const {
		ArboreBinarCautare temp;
		temp.AdaugaArbore(rad);
		temp.AdaugaArbore(other.rad);
		return temp;
	}
	ArboreBinarCautare operator-(const ArboreBinarCautare& other) const {
		ArboreBinarCautare temp;
		temp.AdaugaArbore(rad);
		temp.StergeElementeArbore(other.rad);
		return temp;
	}
	ArboreBinarCautare operator*(const ArboreBinarCautare& other) const {
		ArboreBinarCautare temp;
		temp.AdaugaIntersectie(rad, other.rad);
		return temp;
	}
	///Operatori de citire si afisare
	template<class U>
	friend istream& operator>>(istream&, ArboreBinarCautare<U>&);
	template<class U>
	friend ostream& operator<<(ostream&, const ArboreBinarCautare<U>&);
	///implementare functii virtuale
	bool add(T val) {
		bool ok;
		AdaugaNod(rad, val, ok);
		return ok;
	}
	bool erase(T val) {
		bool ok;
		StergeElement(rad, val, ok);
		return ok;
	}
	int height() const {
		return Inaltime(rad);
	}
	void printLeaves() const {
		afisareFrunze(rad);
		cout << '\n';
	}
	istream& citire(istream& in) {
		StergeArbore(rad);
		int n, val;
		in >> n;
		for (int i = 0; i < n; ++i) {
			in >> val;
			bool ok;
			rad = AdaugaNod(rad, val, ok);
		}
		return in;
	}
	ostream& afisare(ostream& out) const {
		afisareSRD(out, rad);
		return out;
	}
///Functii ajutatoare
protected:
	Nod<T>* CopiazaArbore(Nod<T>* R) {
		if (R)
		{
			Nod<T>* p = new Nod<T>;
			p->info = R->info;
			p->st = CopiazaArbore(R->st);
			p->dr = CopiazaArbore(R->dr);
			return p;
		}
		return nullptr;
	}
	void StergeArbore(Nod<T>* R) {
		if (R)
		{
			StergeArbore(R->st);
			StergeArbore(R->dr);
			delete R;
		}
	}
	void AdaugaArbore(Nod<T>* R) {
		if (R)
		{
			bool ok;
			rad = AdaugaNod(rad, R->info, ok);
			nr_noduri += ok;
			AdaugaArbore(R->st);
			AdaugaArbore(R->dr);
		}
	}
	Nod<T>* AdaugaNod(Nod<T>* R,T val,bool& ok) {
		if (!R) {
			R = new Nod(val);
			return R;
		}
		if (R->info == val) ok = 0;
		else if (R->info < val) R->dr = AdaugaNod(R->dr, val, ok);
		else R->st = AdaugaNod(R->st, val, ok);
		return R;
	}
	void StergeElementeArbore(Nod<T>* R) {
		if (R) {
			bool ok;
			rad = StergeElement(rad, R->info, ok);
			nr_noduri -= ok;
			StergeElementeArbore(R->st);
			StergeElementeArbore(R->dr);
		}
	}
	Nod<T>* StergeElement(Nod<T>* R,T val,bool& ok) {
		if (!R) {
			ok = 0; return nullptr;
		}
		if (R->info < val) R->dr = StergeElement(R->dr, val, ok);
		else if (val < R->info) R->st = StergeElement(R->st, val, ok);
		else {
			if (R->st == nullptr) {
				Nod* p = R->dr;
				delete R;
				return p;
			}
			if (R->dr == nullptr) {
				Nod*p = R->st;
				delete R;
				return p;
			}
			Nod* p = R->st;
			while (p->dr) p = p->dr;
			R->info = p->info;
			ok = 1;
			R->st = StergeElement(R->st, p->info, ok);
		}
		return R;
	}
	void AdaugaIntersectie(Nod<T>* p, Nod<T>* q) {
		if (p) {
			bool ok;
			if (CautaNod(q, p->info)) rad = AdaugaNod(rad, p->info, ok);
			AdaugaIntersectie(p->st, q);
			AdaugaIntersectie(p->dr, q);
		}
	}
	bool CautaNod(Nod<T>* R, T val) {
		if (R) {
			if (R->info == val) return true;
			if (R->info < val) return CautaNod(R->dr, val);
			return CautaNod(R->st, val);
		}
		return false;
	}
	int Inaltime(Nod<T>* R) const {
		if (!R) return -1;
		int aux1 = Inaltime(R->st);
		int aux2 = Inaltime(R->dr);
		if (aux1 < aux2) return 1 + aux2;
		return 1 + aux1;
	}
	void afisareFrunze(Nod<T>* R) const {
		if (R) {
			if (!R->st && !R->dr) cout << *R << ' ';
			else {
				afisareFrunze(R->st);
				afisareFrunze(R->dr);
			}
		}
	}
	void afisareSRD(ostream& out, Nod<T>* R) const {
		if (R) {
			afisareSRD(out, R->st);
			out << *R << ' ';
			afisareSRD(out, R->dr);
		}
	}
};

//Implementari
template<class T>
istream& operator>>(istream& in, ArboreBinarCautare<T>& p) {
	return p.citire(in);
}
template<class T>
ostream& operator<<(ostream& out, const ArboreBinarCautare<T>& p) {
	return p.afisare(out);
}

#endif