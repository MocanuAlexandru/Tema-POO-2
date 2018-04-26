#pragma once
#ifndef __NOD_HEADER_
#define __NOD_HEADER_
#include<istream>
using namespace std;
template <class T>
class ArboreBinarCautare;
template <class T>
class Nod {
protected:
	///Membrii Clasei
	T info;
	Nod *st, *dr, *tata;
	/// Clasa trebuie sa fie prietena cu clasa ABC(ABC are elementele de tip Nod)
	friend class ArboreBinarCautare<T>;
	///Constructori
	Nod() = default;
	Nod(int val) :info(val) {
		st = nullptr;
		dr = nullptr;
	};
	Nod(const Nod& other) {
		info = other.info;
		st = nullptr;
		dr = nullptr;
	}
	Nod& operator=(const Nod& other) {
		info = other.info;
		st = nullptr;
		dr = nullptr;
		return *this;
	}
	///Destructor
	virtual ~Nod() = default;;
	///operatori de comparare
	bool operator==(const Nod& other) const {
		return info == other.info;
	}
	bool operator!=(const Nod& other) const {
		return !(*this == other);
	}
	bool operator<(const Nod&  other) const {
		return info < other.info;
	}
	///Operatori de citire si afisare
	template<class U>
	friend istream& operator>>(istream&, Nod<U>&);
	template<class U>
	friend ostream& operator<<(ostream&, const Nod<U>&);
};

///Implementari
template<class T>
istream& operator>>(istream& in, Nod<T>& p)
{
	in >> p.info;
	p.st = nullptr;
	p.dr = nullptr;
	return in;
}
template<class T>
ostream& operator<<(ostream& out, const Nod<T>& p)
{
	out << p.info;
	return out;
}
#endif

