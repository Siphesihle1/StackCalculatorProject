#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	string operation;
	int choice;

	cout << "Choose\n\n1) Calculate\n2) Calculate extra\n\nEnter choice here: ";
	cin >> choice;

	if (choice == 1) {
		cout << "\nEnter the operation in infix notation: ";
		getline(cin, operation);
		cout << calculate(to_postfix(operation)) << endl;
	} else {

		cout << "\nEnter the operation in post-fix notation: " << endl;
		//getline(cin);
		getline(cin, operation);
		cout << calculate_extra(operation) << endl;
	}


	return 0;
}

