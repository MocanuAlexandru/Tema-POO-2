#pragma once
#ifndef __ARBORE_HEADER_
#define __ARBORE_HEADER_
class Arbore {
protected:
	int nr_noduri;

public:
	Arbore(int val=0) :nr_noduri(val) {}
	virtual bool add(int) = 0;
	virtual bool erase(int) = 0;
	virtual int height() const = 0;
	virtual void printLeaves() const = 0;
	virtual ostream& afisare(ostream&) const = 0;
	virtual istream& citire(istream&) = 0;
	friend istream& operator>>(istream& in, Arbore& R) { return R.citire(in); }
	friend ostream& operator<<(ostream& out, Arbore& R) { return R.afisare(out); }
};
#endif