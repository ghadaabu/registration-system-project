#include "register.h"

using namespace std;


bool fileExists(const string& filename) {
	// checks if the file exists, if yes returns true else returns false
	ifstream file(filename);
	return file.good();
}

bool isLoggedIn()
	// function that checks if a user exists and the provided password is correct, returns true if successful, false elsewise.
{
	string username, password, un, pw;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	string filename = ".//data//" + username + ".txt"; 
	ifstream read(filename);
	if (read.is_open()) {
		getline(read, un);
		getline(read, pw);

		if (un == username && pw == password)
			return true;
		else
			return false;
	}
	cout << "user not found!" << endl;
	return false;
}

int validPassword (const string& password)
	// checks if the provided password is valid, and returns an int based on the following:
	// 0 - if the password is valid.
	// 1 - if the password is shorter than min_size characters or longer than max_size characters.
	// 2 - if the password doesn't contain at least one english letter and at least one number.
{	
	typedef string::size_type size_t;
	size_t len = password.size(), min_size = 8, max_size = 12;
	if (len < min_size || len > max_size)
		return 1;
	bool letter_flag = false, number_flag = false;
	for (size_t i=0; i < len; i++) {
		if (isdigit(password[i]))
			number_flag = true;
		else if(isalpha(password[i]))
			letter_flag = true;
		if (number_flag && letter_flag)
			return 0;
	}
	if (!number_flag || !letter_flag)
		return 2;
	return 0;
}

bool createNewUser()
	// creates new user, if the username is taken returns false and returns true upon successful action.
{
	string username, password;

	cout << "select a username: ";
	cin >> username;
	string filename = ".//data//" + username + ".txt"; 
	if (fileExists(filename)){
		return false;
	}
	cout << "Password must be 8 - 12 characters, contain at least 1 letter and 1 number" << endl << "select a password: ";
	cin >> password;
	if (!cin)
		exit(1);
	int valid = validPassword(password);
	while(valid) {
		if (valid == 2)
			cout << "password must contain at least 1 letter and 1 number" << endl;
		else
			cout << "password must be 8 - 12 characters long" << endl;
		cout << "Enter new password: ";
		cin >> password;
		if (!cin)
			exit(1);
		valid = validPassword(password);
	}

	ofstream file;	
	file.open(filename);
	file << username << endl << password;
	file.close();
	return true;
}
