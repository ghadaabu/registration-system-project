#include <iostream>
#include <sys/types.h>
#include "register.h"
#include "user_mod.h"

using namespace std;

int main()
{
	int choice;
	Register regSystem; 
	UserC user;

	cout << "Select an option:\n1: Register\n2: Login\nYour choice: ";
	while(cin >> choice){

		switch (choice) {
			case 1:
				{
					bool status = regSystem.createNewUser();

					while (!status)
					{
						cout << "Username already taken. Please choose a different username.\n" << endl;
						status = regSystem.createNewUser();
						// return 0;
					}
					cout << "Registration successful! You can now log in." << endl;
					break;
				}
			case 2:
				{ 
					//define user object !!
					int status = regSystem.userLogin(user);

					switch (status) { 
						case 0: // successful login
							{
								// cout << "Successfully logged in!" << endl;
								system("PAUSE");
								return 1;
							}
						case 1: // user doesn't exist
							{
								cout << "User doesn't exist!" << endl;
								// system("PAUSE");
								// return 0;
							}
						case 2: // wrong password
							{
								cout << "Wrong password" << endl;
							}
						default:
							; 
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
