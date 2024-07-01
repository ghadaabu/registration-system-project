#ifndef User_mod
#define User_mod

#include <string>

const std::string DEFAULT_USER = "";

class UserC {
	private:
		std::string username;

	public:
		bool status = false;
		// flag that indicates whether the user is loged in; true if yes, false elsewise

		UserC() : username(DEFAULT_USER) {}
		// default user initilization

		UserC(const std::string& uname) : username(uname) {}
		// initilze the user object with uname

		std::string getUsername() const { return username; }

		void login(const std::string uname) { 
			username = uname;
			status = true;
		}

		void logout() {
			username =  DEFAULT_USER;
			status = false;
		}

};

#endif
