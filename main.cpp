#include<iostream>
#include<fstream>
#include<cstdio>
#include "Nod.h"
#include "Nod_rosu_negru.h"
#include "Arbore.h"
#include "ArboreBinarCautare.h"
#include "ArboreRosuNegru.h"
using namespace std;
int main()
{
	ArboreBinarCautare<int> R1;
	cin >> R1;
	for (ArboreBinarCautare<int>::iterator it = R1.begin(); it != R1.end(); ++it)
		cout << (*it) << ' ';
	cout << '\n';
	cout << '\n';
	system("pause");
	return 0;
}