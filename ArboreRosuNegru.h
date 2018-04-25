#pragma once
#ifndef __ARBORE_ROSU_NEGRU_HEADER_
#define __ARBORE_ROSU_NEGRU_HEADER_
#include "Arbore.h"
#include "Nod_rosu_negru.h"
using namespace std;
template<class T>
class ArboreRosuNegru : public Arbore {
	//Date membre
protected:
	Nod_rosu_negru<T> * rad;
	///Constructori
public:
	ArboreRosuNegru() : Arbore() { rad = nullptr; }
	ArboreRosuNegru(const ArboreRosuNegru& other) {
		rad = CopiazaArbore(other.rad);
		nr_noduri = other.nr_noduri;
	}
	ArboreRosuNegru& operator=(const ArboreRosuNegru& other) {
		StergeArbore(rad);
		rad = CopiazaArbore(other.rad);
		nr_noduri = other.nr_noduri;
		return *this;
	};
	///Destructor
	~ArboreRosuNegru() {
		StergeArbore(rad);
	}
	///operatori de comparare
	bool operator==(const ArboreRosuNegru& other) const {
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
	bool operator!=(const ArboreRosuNegru& other) const {
		return !(*this == other);
	}
	bool operator<(const ArboreRosuNegru& other) const {
		if (other.rad == nullptr) return false;
		if (rad == nullptr) return true;
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
	ArboreRosuNegru operator+(const ArboreRosuNegru& other) const {
		ArboreRosuNegru temp;
		temp.AdaugaArbore(rad);
		temp.AdaugaArbore(other.rad);
		return temp;
	}
	ArboreRosuNegru operator-(const ArboreRosuNegru& other) const {
		ArboreRosuNegru temp;
		temp.AdaugaArbore(rad);
		temp.StergeElementeArbore(other.rad);
		return temp;
	}
	ArboreRosuNegru operator*(const ArboreRosuNegru& other) const {
		ArboreRosuNegru temp;
		temp.AdaugaIntersectie(rad, other.rad);
		return temp;
	}
	///Operatori de citire si afisare
	template <class U>
	friend istream& operator>>(istream&, ArboreRosuNegru<U>&);
	template <class U>
	friend ostream& operator<<(ostream&, const ArboreRosuNegru<U>&);
	///implementare functii virtuale
	bool add(T val) {
		bool ok;
		Nod_rosu_negru* aux = new Nod_rosu_negru(val);
		rad = aux->Insert(rad, ok);
		if (!ok) delete aux;
		return ok;
	}
	bool erase(T val) {
		return Delete(rad, val);
	}
	int height() const {
		return InaltimeNeagra(rad);
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
			Nod_rosu_negru* aux = new Nod_rosu_negru(val);
			rad = aux->Insert(rad, ok);
			if (!ok) delete aux;
		}
		return in;
	}
	ostream& afisare(ostream& out) const {
		afisareSRD(out, rad);
		return out;
	}
	///Functii ajutatoare
protected:
	Nod_rosu_negru<T> * CopiazaArbore(Nod_rosu_negru<T>* R) {
		if (R)
		{
			Nod_rosu_negru* p = new Nod_rosu_negru(*R);
			p->st = CopiazaArbore(R->st);
			p->dr = CopiazaArbore(R->dr);
			return p;
		}
		return nullptr;
	}
	void StergeArbore(Nod_rosu_negru<T>* R) {
		if (R)
		{
			StergeArbore(R->st);
			StergeArbore(R->dr);
			delete R;
		}
	}
	void AdaugaArbore(Nod_rosu_negru<T>* R) {
		if (R)
		{
			bool ok;
			Nod_rosu_negru* aux = new Nod_rosu_negru(R->info);
			rad = aux->Insert(rad, ok);
			if (!ok) delete aux;
			else nr_noduri += ok;
			AdaugaArbore(R->st);
			AdaugaArbore(R->dr);
		}
	}
	void StergeElementeArbore(Nod_rosu_negru<T>* R) {
		if (R) {
			nr_noduri -= Delete(rad, R->info);
			StergeElementeArbore(R->st);
			StergeElementeArbore(R->dr);
		}
	}
	bool Delete(Nod_rosu_negru<T>* R, T val) {
		while (R && R->info != val) {
			if (val < R->info) R = R->st;
			else R = R->dr;
		}
		if (!R) return false;
		if (R->dr && R->st) {
			Nod_rosu_negru* p = R->st;
			while (p->dr) p = p->dr;
			R->info = p->info;
			R = p;
		}
		Nod_rosu_negru* c;
		if (R->dr) c = R->dr;
		else c = R->st;
		if (R == rad && !c) {
			delete R;
			rad = nullptr;
			return true;
		}
		if (R->CuloareNod == Nod_rosu_negru::culoare::rosu) {
			if (R->tata->dr == R) R->tata->dr = nullptr;
			else R->tata->st = nullptr;
			delete R;
			return true;
		}
		if (c && c->CuloareNod == Nod_rosu_negru::culoare::rosu) {
			c->tata = R->tata;
			if (R->parent()) {
				if (R->tata->dr == R) R->tata->dr = c;
				else R->tata->st = c;
			}
			else rad = c;
			c->CuloareNod = Nod_rosu_negru::culoare::negru;
			delete R;
			return true;
		}
		if (c) {
			c->tata = R->tata;
			if (R->parent()) {
				if (R->tata->dr == R) R->tata->dr = c;
				else R->tata->st = c;
			}
			delete R;
			deleteCase1(c);
			rad = c;
			while (rad->parent()) {
				rad = rad->parent();
			}
			return true;
		}
		else {
			deleteCase1(R);
			rad = R;
			while (rad->parent()) rad = rad->parent();
			while (R->dr || R->st) {
				if (val < R->info) R = R->st;
				else if (R->info < val) R = R->dr;
			}
			if (R->tata->dr == R) R->tata->dr = nullptr;
			else R->tata->st = nullptr;
			delete R;
			return true;
		}
	}
	void AdaugaIntersectie(Nod_rosu_negru<T>* p, Nod_rosu_negru<T>* q) {
		if (p) {
			bool ok;
			if (CautaNod_rosu_negru(q, p->info)) {
				Nod_rosu_negru* aux = new Nod_rosu_negru(p->info);
				rad = aux->Insert(rad, ok);
				if (!ok) delete aux;
			}
			AdaugaIntersectie(p->st, q);
			AdaugaIntersectie(p->dr, q);
		}
	}
	bool CautaNod_rosu_negru(Nod_rosu_negru<T>* R, T val) {
		if (R) {
			if (R->info == val) return true;
			if (R->info < val) return CautaNod_rosu_negru(R->dr, val);
			return CautaNod_rosu_negru(R->st, val);
		}
		return false;
	}
	int InaltimeNeagra(Nod_rosu_negru<T>* R) const {
		if (!R) return 0;
		if (R->st) return InaltimeNeagra(R->st) + R->CuloareNod;
		return InaltimeNeagra(R->dr) + R->CuloareNod;
	}
	void afisareFrunze(Nod_rosu_negru<T>* R) const {
		if (R) {
			if (!R->st && !R->dr) cout << *R << ' ';
			else {
				afisareFrunze(R->st);
				afisareFrunze(R->dr);
			}
		}
	}
	void afisareSRD(ostream& out, Nod_rosu_negru<T>* R) const {
		if (R) {
			afisareSRD(out, R->st);
			out << *R << ' ';
			afisareSRD(out, R->dr);
		}
	}
	void deleteCase1(Nod_rosu_negru<T>* c) {
		if (c->parent() == nullptr) {
			rad = c;
			return;
		}
		deleteCase2(c);
	}
	void deleteCase2(Nod_rosu_negru<T>* c) {
		Nod_rosu_negru* s = c->sibling();
		if (s && s->CuloareNod == Nod_rosu_negru::culoare::rosu) {
			c->parent()->CuloareNod = Nod_rosu_negru::culoare::rosu;
			s->CuloareNod = Nod_rosu_negru::culoare::negru;
			if (c == c->parent()->st) {
				c->parent()->rotate_right_left();
			}
			else c->parent()->rotate_left_right();
		}
		deleteCase3(c);
	}
	void deleteCase3(Nod_rosu_negru<T>* c) {
		Nod_rosu_negru* s = c->sibling();
		if (c->parent()->CuloareNod == Nod_rosu_negru::culoare::negru && s->CuloareNod == Nod_rosu_negru::culoare::negru && (!s->dr || s->dr->CuloareNod == Nod_rosu_negru::culoare::negru) && (!s->st || s->st->CuloareNod == Nod_rosu_negru::culoare::negru)) {
			s->CuloareNod = Nod_rosu_negru::culoare::rosu;
			deleteCase1(c->parent());
		}
		else deleteCase4(c);
	}
	void deleteCase4(Nod_rosu_negru<T>* c) {
		Nod_rosu_negru* s = c->sibling();
		if (c->parent()->CuloareNod == Nod_rosu_negru::culoare::rosu && s->CuloareNod == Nod_rosu_negru::culoare::negru && (!s->dr || s->dr->CuloareNod == Nod_rosu_negru::culoare::negru) && (!s->st || s->st->CuloareNod == Nod_rosu_negru::culoare::negru)) {
			s->CuloareNod = Nod_rosu_negru::culoare::rosu;
			c->parent()->CuloareNod = Nod_rosu_negru::culoare::negru;
		}
		else deleteCase5(c);
	}
	void deleteCase5(Nod_rosu_negru<T>* c) {
		Nod_rosu_negru* s = c->sibling();
		if (s->CuloareNod == Nod_rosu_negru::culoare::negru) {
			if (c == c->parent()->st && (!s->dr || s->dr->CuloareNod == Nod_rosu_negru::culoare::negru) && (s->st && s->st->CuloareNod == Nod_rosu_negru::culoare::rosu)) {
				s->CuloareNod = Nod_rosu_negru::culoare::rosu;
				s->st->CuloareNod = Nod_rosu_negru::culoare::negru;
				s->rotate_left_right();
			}
			else if (c == c->parent()->dr && (!s->st || s->st->CuloareNod == Nod_rosu_negru::culoare::negru) && (s->dr && s->dr->CuloareNod == Nod_rosu_negru::culoare::rosu)) {
				s->CuloareNod = Nod_rosu_negru::culoare::rosu;
				s->dr->CuloareNod = Nod_rosu_negru::culoare::negru;
				s->rotate_right_left();
			}
			deleteCase6(c);
		}
	}
	void deleteCase6(Nod_rosu_negru<T>* c) {
		Nod_rosu_negru* s = c->sibling();
		s->CuloareNod = c->parent()->CuloareNod;
		c->parent()->CuloareNod = Nod_rosu_negru::culoare::negru;
		if (c == c->parent()->st) {
			s->dr->CuloareNod = Nod_rosu_negru::culoare::negru;
			s->parent()->rotate_right_left();
		}
		else {
			s->st->CuloareNod = Nod_rosu_negru::culoare::negru;
			s->parent()->rotate_left_right();
		}
	}
};

//Implementari
template <class T>
istream& operator>>(istream& in, ArboreRosuNegru<T>& p) {
	return p.citire(in);
}
template <class T>
ostream& operator<<(ostream& out, const ArboreRosuNegru<T>& p) {
	return p.afisare(out);
}

#endif