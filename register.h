#ifndef Register_header
#define Register_header

#include "user_mod.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <unordered_map>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>

class Register {
	private:
		bool usernameExists(const std::string& username);
		// checks if username exists, returns true if exists and false if not.

		void storeUserData(const std::unordered_map<std::string, std::string>& userdata);
		// function to store user data

		bool updateUserData(const std::string& username, const std::string& newHashedPassword);
		// function that updates the user data, after changing the password.
		// uses a temporary file to store the user_data.txt file contenct, it updates the password for the user while storing the date into the temp file. 
		// at the end it changes the new file name into the original file name i.e. user_data.txt, and removes the old file.
		// returns true apon successfull update and false upon failure.


	public:
		int userLogin(UserC& user);
		// function that checks if a user exists and the provided password is correct. 
		// Returns 0 if successful, 1 if username does not exist, and 2 if the password is incorrect.
		
		std::string getValidPassword();
		// function that requests from the user to input a password and checks if the password is valid, if not it keeps requiesting. if valid, returns the password.

		int checkIfValidPassword (const std::string& password);
		// checks if the provided password is valid, and returns an int based on the following:
		// 0 - if the password is valid.
		// 1 - if the password is shorter than min_size characters or longer than max_size characters.
		// 2 - if the password doesn't contain at least one english letter and at least one number and no space.

		bool createNewUser();
		// creates new user, if the username is taken returns false and returns true upon successful action.


		std::string hashPassword(const std::string& password);
		// function to hash a password using sha-256

		
		std::unordered_map<std::string, std::string> loadUserData();
		// function to load user data

		bool changePassword(const std::string& username);
		// change the password for existing user.
};

#endif
