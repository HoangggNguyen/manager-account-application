#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include "AccountEntity.cpp"

class AccountRepository {

public:
	void createAccount(const std::string& userName, const std::string& password, bool isActive, const std::string& maker);
	void deleteAccount(const std::string& userName);
	void updateAccount(const std::string& userName, const std::string& newPassword, bool newIsActive);
	AccountEntity getAccount(const std::string& userName);
	bool checkAccountLogin(const std::string& userName, const std::string& password);
};
