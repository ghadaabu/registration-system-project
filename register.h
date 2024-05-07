#ifndef Register
#define Register

#include <iostream>
#include <string>
#include <fstream>

bool fileExists(const std::string&);
// checks if the file exists, if yes returns true else returns false

bool isLoggedIn();
// function that checks if a user exists and the provided password is correct, returns true if successful, false elsewise.

int validPassword (const std::string& password);
// checks if the provided password is valid, and returns an int based on the following:
// 0 - if the password is valid.
// 1 - if the password is shorter than min_size characters or longer than max_size characters.
// 2 - if the password doesn't contain at least one english letter and at least one number.

bool createNewUser();
// creates new user, if the username is taken returns false and returns true upon successful action.
#endif
