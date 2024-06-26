#include <iostream>
#include "register.h"

using namespace std;

int main()
{
	int choice;

	cout << "Select an option:\n1: Register\n2: Login\nYour choice: ";
	while(cin >> choice){

		switch (choice) {
			case 1:
				{
					bool status = createNewUser();

					while (!status)
					{
						cout << "Username already taken. Please choose a different username.\n" << endl;
						status = createNewUser();
						// return 0;
					}
					cout << "Registration successful! You can now log in." << endl;
					break;
				}
			case 2:
				{
					bool status = isLoggedIn();

					if (!status)
					{
						// cout << "False Login!" << endl;
						// system("PAUSE");
						// return 0;
					}
					else 
					{
						// cout << "Successfully logged in!" << endl;
						system("PAUSE");
						return 1;
					}
					break;
				}
			default:
				cout << "Please select action!" << endl;
				cin.clear();

		}
		cout << "\nSelect an option:\n1: Register\n2: Login\nYour choice: ";
	}
	return 0;
}
