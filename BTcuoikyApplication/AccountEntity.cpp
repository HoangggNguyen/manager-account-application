#include <iostream>
#include <string>
#include <ctime>

class AccountEntity {
private:
	int id;
	std::string userName;
	std::string password;
	bool isActive;
	std::string createdDate;
	std::string maker;
	bool isAdmin;

public:
	AccountEntity() {}
	//generic constructor
	AccountEntity(int& id,std::string& userName, std::string& password, bool isActive, std::string& maker,
		time_t& updatedDate, std::string& userUpdated)
		: userName(userName), password(password), isActive(isActive), maker(maker) {
	}

	void setId(int id) {
		this->id = id;
	}
	int getId() const {
		return id;
	}

	// Getter and Setter for userName
	std::string getUserName() const {
		return userName;
	}

	void setUserName(const std::string& user) {
		userName = user;
	}

	// Getter and Setter for password
	std::string getPassword() const {
		return password;
	}

	void setPassword(const std::string& pass) {
		password = pass;
	}

	// Getter and Setter for isActive
	bool getIsActive() const {
		return isActive;
	}

	void setIsActive(bool active) {
		isActive = active;
	}

	void setCreatedDate(const time_t& date) {
		createdDate = date;
	}

	// Getter and Setter for maker
	std::string getMaker() const {
		return maker;
	}

	void setMaker(const std::string& mkr) {
		maker = mkr;
	}
	// Getter and Setter for isAdmin
	bool getIsAdmin() const {
		return isAdmin;
	}
	void setIsAdmin(bool admin) {
		isAdmin = admin;
	}

};