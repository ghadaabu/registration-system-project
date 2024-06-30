#ifndef User_mod
#define User_mod

#include <string>

class UserC {
	private:
		std::string username;

	public:
		UserC(const std::string& uname) : username(uname) {}
		// initilze the user object with uname

		std::string getUsername() const { return username; }

};

#endif
