#include "register.h"

using namespace std;

bool isLoggedIn()
	// function that checks if a user exists and the provided password is correct, returns true if successful, false elsewise.
{
	unordered_map<string, string> userData = loadUserData();
	string username, password, un, pw;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	if (userData.find(username) == userData.end()) {
		cout << "Username does not exist." << endl;
		return false;
	}

	string hashedPassword = hashPassword(password);
	if (hashedPassword == userData[username]) {
		cout << "Login successful!" << endl;
		return true;
	} else {
		cout << "Incorrect password." << endl;
		return false;
	}
}

int validPassword (const string& password)
	// checks if the provided password is valid, and returns an int based on the following:
	// 0 - if the password is valid.
	// 1 - if the password is shorter than min_size characters or longer than max_size characters.
	// 2 - if the password doesn't contain at least one english letter and at least one number and no space.
{	
	typedef string::size_type size_t;
	size_t len = password.size(), min_size = 8, max_size = 12;
	if (len < min_size || len > max_size)
		return 1;
	if (password.find(' ') != string::npos)
		return 2;
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
	unordered_map<string, string> userData = loadUserData();

	cout << "select a username: ";
	cin >> username;

	if (userData.find(username) != userData.end()) {
		return false;
	}

	cout << "Password must be 8 - 12 characters, contain at least 1 letter and 1 number and no spaces" << endl << "select a password: ";
	cin >> password;
	if (!cin)
		exit(1);
	int valid = validPassword(password);
	while(valid) {
		if (valid == 2)
			cout << "password must contain at least 1 letter and 1 number and no space" << endl;
		else
			cout << "password must be 8 - 12 characters long" << endl;
		cout << "Enter new password: ";
		cin >> password;
		if (!cin)
			exit(1);
		valid = validPassword(password);
	}

	string hashedPassword = hashPassword(password);
	userData[username] = hashedPassword;
	storeUserData(userData);

	return true;
}

// Function to hash a password using SHA-256
string hashPassword(const string& password) {
	CryptoPP::SHA256 hash;
	string digest;

	// Process the input password, hash it, encode it to hexadecimal, and save to digest
	CryptoPP::StringSource(password, true,
			new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(digest)
					)
				)
			);

	return digest;
}

// Function to store user data
void storeUserData(const unordered_map<string, string>& userData) {
	ofstream file("user_data.txt");
	for (const auto& [username, hashedPassword] : userData) {
		file << username << " " << hashedPassword << "\n";
	}
	file.close();
}

// Function to load user data
unordered_map<string, string> loadUserData() {
	unordered_map<string, string> userData;
	ifstream file("user_data.txt");
	string username, hashedPassword;
	while (file >> username >> hashedPassword) {
		userData[username] = hashedPassword;
	}
	file.close();
	return userData;
}

