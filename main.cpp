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

	while (true){
		if (user.isLoggedIn()) { // logged in 
			cout << "\n1: Logout\n2: Change password\nYour choice: ";
			cin >> choice;
			switch (choice) {
				case 1:
					{
						user.logout();
						cout << "Logout successful!" << endl;
						break;
					}
				case 2: 
					{
						if (regSystem.changePassword(user.getUsername()))
							cout << "Password changed!" << endl;
						break;

					}
				default:
					cout << "Please select a valid action!" << endl;	
					break;
				break;
			}

		} else {
			cout << "\n1: Register\n2: Login\n3: Exit program\nYour choice: ";
			cin >> choice;

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
									cout << "Successfully logged in!" << endl;
									break;
								}
							case 1: // user doesn't exist
								{
									cout << "User doesn't exist!" << endl;
									// system("PAUSE");
									break;
								}
							case 2: // wrong password
								{
									cout << "Wrong password" << endl;
									break;
								}
							default:
								break;
						}
						break;
					}
				case 3:
					return 0;
				default:
					cout << "Please select action!" << endl;
					cin.clear();
					break;
			}
		}
	}
	return 0;
}
