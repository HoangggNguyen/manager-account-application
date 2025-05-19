#include <iostream>
#include <string>
#include <ctime>

class PersonalUser {
private:
	int id;
	std::string fullName;
	std::string dateOfBirth;
	std::string gender;
	std::string address;
	std::string email;
	std::string phoneNumber;
	int accountId;
	bool isActive;

public:
	PersonalUser() {}

	//generic constructor 
	PersonalUser(int& id, std::string& fullName, std::string& dateOfBirth, std::string& address, std::string& email,
		std::string& phoneNumber, int& accountId, bool& isActive)
		: id(id), fullName(fullName), dateOfBirth(dateOfBirth), address(address), email(email), phoneNumber(phoneNumber),
		accountId(accountId), isActive(isActive) {

	}

	// Getter and Setter for fullName
	std::string getFullName() const {
		return fullName;
	}
	void setFullName(const std::string& name) {
		fullName = name;
	}
	// Getter and Setter for dateOfBirth
	std::string getDateOfBirth() const {
		return dateOfBirth;
	}
	void setDateOfBirth(const std::string& dob) {
		dateOfBirth = dob;
	}
	//Getter and setter address
	std::string getAddress() const {
		return address;
	}
	void setAddress(const std::string& addr) {
		address = addr;
	}
	//Getter and setter email
	std::string getEmail() const {
		return email;
	}
	void setEmail(const std::string& mail) {
		email = mail;
	}
	//Getter and setter phoneNumber
	std::string getPhoneNumber() const {
		return phoneNumber;
	}
	void setPhoneNumber(const std::string& phone) {
		phoneNumber = phone;
	}
	//Getter and setter gender
	std::string getGender() const {
		return gender;
	}

	void setGender(std::string gen) {
		gender = gen;
	}

	void setId(int id) {
		this->id = id;
	}
	int getId() const {
		return id;
	}

	// Getter and Setter for accountId
	int getAccountId() const {
		return accountId;
	}
	void setAccountId(int accId) {
		accountId = accId;
	}

	bool getIsActive() const {
		return isActive;
	}
	void setIsActive(bool active) {
		isActive = active;
	}

};