#include <iostream>
#include "SLAU.h"

using namespace std;

int main()
{
	bool exit = false;
	bool check = true;
	bool generation;
	int size;

	cout << "Enter Size:" << endl; cin >> size;
	cout << "Choise: \n1) random generate \n0) enter from keyboard\n" << endl; cin >> generation;
	cout << endl;

	SLAU Gauss(size, generation); 
	try
	{
		if (Gauss.solve(check)) 
			cout << "solved!" << "\n";
		else
			cout << "not resolved!" << "\n";
	}
	catch (exception& ex)
	{
		cout << "Error" << ex.what() << "\n";
	}
	
}