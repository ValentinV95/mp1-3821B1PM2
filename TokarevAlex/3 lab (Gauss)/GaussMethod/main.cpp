#include <iostream>
#include "SLAU.h"

using namespace std;

int main()
{
	bool exit = false;
	bool check_actvated;
	bool auto_generation;
	int size;

	while (!exit) 
	{
		cout << "Enter Size!" << endl; cin >> size;
		cout << "Press 1 to activate correct check, 0 to continue" << endl; cin >> check_actvated;
		cout << "Press 1 to generate SLAU, 0 to enter from keyboard" << endl; cin >> auto_generation;
		cout << endl;

		SLAU Gauss(size, auto_generation); //system initialization
		try
		{
			if (Gauss.solve(check_actvated)) // solve system
				cout << "solved!" << "\n\n";
			else 
				cout << "not resolved!" << "\n\n";
		}
		catch (exception& ex)
		{
			cout << "ERROR!" << ex.what()<< "\n\n";
		}
		cout << "Press 1 to exit, press 0 to continue" << endl; cin >> exit; cout << endl;
	}
 }
	