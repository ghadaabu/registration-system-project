#include "register.h"

using namespace std;


bool Register::usernameExists(const string& username) 
// checks if username exists, returns true if exists and false if not.
{
	unordered_map<string, string> userData = Register::loadUserData();
	if (userData.find(username) == userData.end())
		return false;
	return true;
}

int Register::userLogin(UserC& user)
	// function that checks if a user exists and the provided password is correct. 
	// Returns 0 if successful, 1 if username does not exist, and 2 if the password is incorrect.
{
	string username, password, un, pw;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	if (!Register::usernameExists(username)) return 1;

	unordered_map<string, string> userData = Register::loadUserData();

	string hashedPassword = Register::hashPassword(password);
	if (hashedPassword == userData[username]) {
		user.setUsername(username);
		return 0;
	} 
	else {
		return 2;
	}
}

int Register::checkIfValidPassword (const string& password)
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

string Register::getValidPassword()
// function that requests from the user to input a password and checks if the password is valid, if not it keeps requiesting. if valid, returns the password.
{
	string password;
	cout << "Password must be 8 - 12 characters, contain at least 1 letter and 1 number and no spaces" << endl << "select a password: ";
	cin >> password;
	if (!cin)
		exit(1);
	int valid = Register::checkIfValidPassword(password);
	while(valid) {
		if (valid == 2)
			cout << "password must contain at least 1 letter and 1 number and no space" << endl;
		else
			cout << "password must be 8 - 12 characters long" << endl;
		cout << "Enter new password: ";
		cin >> password;
		if (!cin)
			exit(1);
		valid = Register::checkIfValidPassword(password);
	}

	return password;
}

bool Register::createNewUser()
// creates new user, if the username is taken returns false and returns true upon successful action.
{
	string username, password;
	unordered_map<string, string> userData = Register::loadUserData();

	cout << "select a username: ";
	cin >> username;

	if (userData.find(username) != userData.end()) {
		return false;
	}

	password = Register::getValidPassword();	

	string hashedPassword = Register::hashPassword(password);
	userData[username] = hashedPassword;
	Register::storeUserData(userData);

	return true;
}

// Function to hash a password using SHA-256
string Register::hashPassword(const string& password) {
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
void Register::storeUserData(const unordered_map<string, string>& userData) {
	ofstream file("user_data.txt");
	for (const auto& [username, hashedPassword] : userData) {
		file << username << " " << hashedPassword << "\n";
	}
	file.close();
}

// Function to load user data
unordered_map<string, string> Register::loadUserData() {
	unordered_map<string, string> userData;
	ifstream file("user_data.txt");
	string username, hashedPassword;
	while (file >> username >> hashedPassword) {
		userData[username] = hashedPassword;
	}
	file.close();
	return userData;
}

bool Register::updateUserData(const string& username, const string& newHashedPassword) 
// function that updates the user data, after changing the password.
// uses a temporary file to store the user_data.txt file contenct, it updates the password for the user while storing the date into the temp file. 
// at the end it changes the new file name into the original file name i.e. user_data.txt, and removes the old file.
// returns true apon successfull update and false upon failure.
{
    ifstream infile("user_data.txt");
    ofstream outfile("temp_user_data.txt");

    if (!infile) {
        cerr << "Error: Failed to open user_data.txt for reading." << endl;
        return false;
    }

    if (!outfile) {
        cerr << "Error: Failed to open temp_user_data.txt for writing." << endl;
        return false;
    }

    bool userFound = false;
    string line;

    while (getline(infile, line)) {
        istringstream iss(line);
        string currentUsername, currentHashedPassword;
        
        if (!(iss >> currentUsername >> currentHashedPassword)) {
            cerr << "Error: Failed to parse line in user_data.txt." << endl;
            continue;
        }

        if (currentUsername == username) {
            outfile << username << " " << newHashedPassword << "\n";
            userFound = true;
        } else {
            outfile << currentUsername << " " << currentHashedPassword << "\n";
        }
    }

    infile.close();
    outfile.close();

    if (!userFound) {
        cerr << "Error: Username \"" << username << "\" not found in user_data.txt." << endl;
        // Delete the temporary file since no update was made
        remove("temp_user_data.txt");
        return false;
    }

    // Replace the original file with the updated temporary file
    if (rename("temp_user_data.txt", "user_data.txt") != 0) {
        cerr << "Error: Failed to rename temp_user_data.txt to user_data.txt." << endl;
        // Clean up by removing the temporary file
        remove("temp_user_data.txt");
        return false;
    }

    return true;
}

bool Register::changePassword(const string& username) {
// change the password for existing user.
	cout << "Please Enter the new password \n";
	string password = Register::getValidPassword();
	string hashedPassword = Register::hashPassword(password);
	
	unordered_map<string, string> userData = Register::loadUserData();
	userData[username] = hashedPassword;
	Register::storeUserData(userData);

	return true;
	
}
