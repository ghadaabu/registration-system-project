#ifndef User_mod
#define User_mod

#include <string>

class UserC {
	private:
		std::string username;

	public:
		UserC() : username("") {}

		UserC(const std::string& uname) : username(uname) {}
		// initilze the user object with uname

		void setUsername(const std::string uname) { username = uname; }

		std::string getUsername() const { return username; }

};

#endif
