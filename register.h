#ifndef Register
#define Register

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>


bool isLoggedIn();
// function that checks if a user exists and the provided password is correct, returns true if successful, false elsewise.

int validPassword (const std::string& password);
// checks if the provided password is valid, and returns an int based on the following:
// 0 - if the password is valid.
// 1 - if the password is shorter than min_size characters or longer than max_size characters.
// 2 - if the password doesn't contain at least one english letter and at least one number and no space.

bool createNewUser();
// creates new user, if the username is taken returns false and returns true upon successful action.

std::string hashPassword(const std::string& password);
// Function to hash a password using SHA-256

void storeUserData(const std::unordered_map<std::string, std::string>& userData);
// Function to store user data

std::unordered_map<std::string, std::string> loadUserData();
// Function to load user data
#endif
