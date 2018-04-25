#pragma once
#ifndef __NOD_ROSU_NEGRU_HEADER_
#define __NOD_ROSU_NEGRU_HEADER_
#include "Nod.h"
template <class T>
class ArboreRosuNegru;
template <class T>
class Nod_rosu_negru : public Nod<T> {
protected:
	//Membrii clasei
	enum culoare { rosu = 0, negru } CuloareNod;
	Nod_rosu_negru* st,*dr,*tata;
	//Clasa trebuie sa fie prietena a clasei ARN
	friend class ArboreRosuNegru<T>;
	//Constructori
	Nod_rosu_negru() :Nod<T>() {}
	Nod_rosu_negru(T val) :Nod<T>(val) {}
	Nod_rosu_negru(T val, int cul) : Nod<T>(val) {
		if (cul % 2) CuloareNod = negru;
		else CuloareNod = rosu;
	}
	Nod_rosu_negru(const Nod_rosu_negru& other) : Nod<T>(other), CuloareNod(other.CuloareNod) {}
	Nod_rosu_negru& operator=(const Nod_rosu_negru& other) {
		info = other.info;
		st = nullptr;
		dr = nullptr;
		CuloareNod = other.CuloareNod;
		return *this;
	}
	//Destructor
	~Nod_rosu_negru() = default;
	//Operator de citire si afisare
	//friend ostream& operator<<(ostream&, const Nod_rosu_negru&);//Trebuie sa afisez si culoarea?
	//Functii ajutatoare pentru ARN
protected:
	Nod_rosu_negru* parent() { return tata; }
	Nod_rosu_negru* grandparent() { 
	Nod_rosu_negru* aux = parent(); 
		if (aux == nullptr) return nullptr;
		return aux->parent();
	}
	Nod_rosu_negru* sibling() {
		Nod_rosu_negru* aux = parent();
		if (aux == nullptr) return nullptr;
		if(this==aux->st) return aux->dr;
		return aux->st;
	}
	Nod_rosu_negru* uncle() {
		Nod_rosu_negru* aux = parent();
		if (aux == nullptr) return nullptr;
		return aux->sibling();
	}
	void rotate_right_left() {//rotate left
		Nod_rosu_negru* R = parent();
		Nod_rosu_negru* p = dr;
		if (p == NULL) return;
		Nod_rosu_negru* q = p->st;
		dr = q;
		if (q) q->tata = this;
		p->st = this;
		p->tata = tata;
		tata = p;
		if (R)
		{
			if (R->dr == this) R->dr = p;
			else R->st = p;
		}
	}
	void rotate_left_right() { //rotate right 
		Nod_rosu_negru* R = parent();
		Nod_rosu_negru* p = st;
		if (p == NULL) return;
		Nod_rosu_negru* q = p->dr;
		st = q;
		if (q) q->tata = this;
		p->dr = this;
		p->tata = tata;
		tata = p;
		if (R)
		{
			if (R->dr == this) R->dr = p;
			else R->st = p;
		}
	}
	void rotate_left_left() {
		Nod_rosu_negru* R = parent();
		Nod_rosu_negru* p = st;
		if (p == NULL) return;
		st = p->dr;
		if (p->dr) p->dr->tata = this;
		p->dr = this;
		p->tata = tata;
		tata = p;
		if (R)
		{
			if (R->dr == this) R->dr = p;
			else R->st = p;
		}
	}
	void rotate_right_right() {
		Nod_rosu_negru* R = parent();
		Nod_rosu_negru* p = dr;
		if (p == NULL) return;
		dr = p->st;
		if (p->st) p->st->tata = this;
		p->st = this;
		p->tata = tata;
		tata = p;
		if (R)
		{
			if (R->dr == this) R->dr = p;
			else R->st = p;
		}
	}
	void Repair() {
		if (parent() == nullptr) {
			CuloareNod = negru;
			return;
		}
		if (parent()->CuloareNod == negru) return;
		Nod_rosu_negru* p = uncle();
		if (p && p->CuloareNod == rosu) {
			parent()->CuloareNod = negru;
			uncle()->CuloareNod=negru;
			grandparent()->CuloareNod = rosu;
			grandparent()->Repair();
			return;
		}
		p = grandparent();
		Nod_rosu_negru* n = this;
		if (p->dr && this == p->dr->st) {
			parent()->rotate_left_right();
			n = dr;
		}
		else if (p->st && this == p->st->dr) {
			parent()->rotate_right_left();
			n = st;
		}
		if (n == n->parent()->st) {
			n->grandparent()->rotate_left_left();
		}
		else n->grandparent()->rotate_right_right();
		n->parent()->CuloareNod = negru;
		n->sibling()->CuloareNod = rosu;
	}
	bool SearchInsert(Nod_rosu_negru* R) {
		if (R != nullptr && info < R->info) {
			if (R->st != nullptr) {
				return SearchInsert(R->st);
			}
			R->st = this;

		}
		else if (R != nullptr) {
			if (info == R->info) return 0;
			if (R->dr != nullptr) {
				return SearchInsert(R->dr);
			}
			R->dr = this;
		}
		tata = R;
		return 1;
	}
	Nod_rosu_negru* Insert(Nod_rosu_negru* R, bool& ok) {
		SearchInsert(R);
		Repair();
		R = this;
		while (R->parent() != nullptr) R = R->parent();
		return R;
	}
};
#endif